#include "services/SensorService.h"


#include <map>
#include <iostream>
using namespace std;

SensorService::SensorService(vector<Attribute *> attributes, vector<Sensor *> sensors){
    this->attributes = move(attributes);
    this->sensors = move(sensors);
}

vector<Sensor *> SensorService::getSensors() {
    return sensors;
}

vector<Attribute *> SensorService::getAttributes() {
    return attributes;
}

Sensor * SensorService::getSensor(string identifier) {

    for(Sensor * sensor : this->sensors)
    {
        if(sensor->getIdentifier()==identifier)
        {
            return sensor;
        }
    }
    return nullptr;
}


// functions for FR5 algorithm
double SensorService::FR5_malfunctioningAnalysis(Sensor sensorToCheck) {
    double relativeSum = 0.0;
    int nbOfMeasurementsForSensorToCheck = 0;
    


    // for every measurement of the sensor, check if it is close to the expected one or not by adding to relative sum
    for(auto &measurement : sensorToCheck.getMeasurements()) {
        // we are looking for 1 year before the time of the first measure
        // this is because example data are from 2019 but in a real app, we would
        // only check for 1 year before the current year
        //std::vector<Measurement *> sensorToCheckMeasurements = sensorToCheck.getMeasurements();
        time_t oneYearBeforeMeasurement = measurement->getTimestamp() - 31536000; // 31536000 == nb seconds 1 year
        // need to apply a modified version of FR8 without taking the sensor values for computation
        map<Attribute*, double> expectedValues = FR8_qualityAttributesExcludeSensor(
            measurement->getSensor()->getLatitude(), 
            measurement->getSensor()->getLongitude(), 
            oneYearBeforeMeasurement,
            sensorToCheck
        );
        double expectedValue = expectedValues[measurement->getAttribute()];
        double relativeDiff = abs(expectedValue - measurement->getValue()) / expectedValue; // compute the relative difference

        relativeSum = relativeSum + relativeDiff;
        nbOfMeasurementsForSensorToCheck = nbOfMeasurementsForSensorToCheck + 1;
    }

    double averageRelativeGap = relativeSum / nbOfMeasurementsForSensorToCheck;
    
    return averageRelativeGap;

}

// functions for FR7 algoriithm
double SensorService::FR7_averageValue(
        Sensor sensor, 
        Attribute targetAttribute, 
        time_t t1, 
        time_t t2
    ) {
    double sum = 0;
    int checkedMeasurement = 0;
    for(auto &measurement : sensor.getMeasurements()) {
        if(
            (measurement->getAttribute()->getIdentifier() == 
            targetAttribute.getIdentifier()) &&
            (measurement->getTimestamp() >= t1) &&
            (measurement->getTimestamp() <= t2)
        ) {
            sum += measurement->getValue();
            checkedMeasurement++;
        }
    }

    if(checkedMeasurement!=0) {
        return sum/checkedMeasurement;
    } else {
        return NULL; //can't divide by zero
    }
}

map<Sensor, double, SensorComparator> SensorService::FR7_sensorComparison(
        Sensor sensorToCompare, 
        time_t t1, 
        time_t t2
    ) {

    //Check if the sensor is in the database by asking for the sensor's identified
    if(getSensor(sensorToCompare.getIdentifier()) == nullptr) {
        return {};
    }

    map<Sensor, double, SensorComparator> proximity;

    //Stores the average value of the target sensor
    map<Attribute, double, AttributeComparator> refValues; 
    for(int i = 0; i < attributes.size(); i++) {
        Attribute currentAttribute = *attributes[i];
        double attributeValue = FR7_averageValue(sensorToCompare, currentAttribute, t1, t2);
        refValues.insert(std::pair<Attribute, double>(currentAttribute, attributeValue));
    }

    for(Sensor* sensor : sensors) {
        if(sensor->getIdentifier() != sensorToCompare.getIdentifier()) {
            double relativeGap = 0;
            int countedMeasurements = 0; 
            for(int i = 0; i < attributes.size(); i++) {
                Attribute currentAttribute = *attributes[i];
                double currentAverage = FR7_averageValue(
                    *sensor, currentAttribute, t1, t2
                );
                double currentRefValue = refValues[currentAttribute];
                if(currentRefValue != NULL && currentAverage != NULL) {
                    relativeGap += abs(currentAverage - currentRefValue)/currentRefValue;
                    countedMeasurements++;
                }
            }
            if(countedMeasurements>0) {
                relativeGap = relativeGap/countedMeasurements;
                proximity[*sensor] = 1/(relativeGap + 1);
            } else { //if the sensor had no measurements, the relative gap can't be calculated, thus we can't compare sensors 
                proximity[*sensor] = NULL;
            }
        }
    }

    return proximity;

}

map<Attribute *,double> SensorService::FR8_qualityAttributes(double latitude, double longitude, time_t time) {
    vector<Measurement *> allMeasurements = getAllMeasurements();

    map<Attribute *,double> numeratorS;
    map<Attribute *,double> denominatorS;
    
    for(auto &it : attributes) {
        numeratorS[it] = denominatorS[it] = 0.0;
    }

    for(auto &it : allMeasurements) {
        if(it->getSensor()->getReliable() && isGivenTimeInsideTimePeriod(time,it->getTimestamp())) {
            //The further away the sensor, the lesser its coefficient.
            double coef = 1.0/distanceBetweenPositions(latitude,longitude,it->getSensor()->getLatitude(),it->getSensor()->getLongitude());
            numeratorS[it->getAttribute()] += coef*it->getValue();
            denominatorS[it->getAttribute()] += coef;
        }
    }

    //Determines the average value.
    for(auto &it : attributes) {
        if(denominatorS[it] != 0) { //Do the final ratio only if we found at least one value. Else we would divide by zero
            numeratorS[it] = numeratorS[it] / denominatorS[it];
        } else { //In that case, defines a null value
            numeratorS[it] = NULL;
        }
    }
    
    return numeratorS;
}


//This is a copy pasted versio of the previous FR8_qualityAttributes, but we ban measures if they're from
//A specified snesor
map<Attribute*, double> SensorService::FR8_qualityAttributesExcludeSensor(
        double latitude, 
        double longitude, 
        time_t time, 
        Sensor& sensorToExclude
    ) {

    vector<Measurement *> allMeasurements = getAllMeasurements();

    map<Attribute *,double> numeratorS;
    map<Attribute *,double> denominatorS;
    
    for(auto &it : attributes) {
        numeratorS[it] = denominatorS[it] = 0.0;
    }

    for(auto &it : allMeasurements) {
        if(it->getSensor()->getReliable() && it->getSensor()->getIdentifier() != sensorToExclude.getIdentifier() && (time,it->getTimestamp())) {
            //The further away the sensor, the lesser its coefficient.
            double coef = 1.0/distanceBetweenPositions(latitude,longitude,it->getSensor()->getLatitude(),it->getSensor()->getLongitude());
            numeratorS[it->getAttribute()] += coef*it->getValue();
            denominatorS[it->getAttribute()] += coef;
        }
    }

    //Determines the average value.
    for(auto &it : attributes) {
        if(denominatorS[it] != 0) { //Do the final ratio only if we found at least one value. Else we would divide by zero
            numeratorS[it] = numeratorS[it] / denominatorS[it];
        } else { //In that case, defines a null value
            numeratorS[it] = NULL;
        }
    }
    
    return numeratorS;

}

string SensorService::FR8_quality(double latitude, double longitude, time_t time) {

    //Converts attributes to string to ease the ATMO score algor
    map<Attribute *,double> meanAttributes = FR8_qualityAttributes(latitude,longitude,time);
    
    map<string,double> stringAttributes;
    for(auto &it : meanAttributes) {
        stringAttributes[it.first->getIdentifier()] = it.second;
    }

    return convertValuesAttributesToATMOScore(stringAttributes);
}

vector<Measurement *> SensorService::getAllMeasurements(){
    vector <Measurement *> measurements;
    for(Sensor * sensor : this->sensors){
        for(Measurement * measurement : sensor->getMeasurements()){
            measurements.push_back(measurement);
        }
    }
    return measurements;
}

//Returns true if t1 is in the interval of [t2-24h;t2+24h]
//Reminder : time_t is just a counter of seconds. So easy to do arithmetics
bool SensorService::isGivenTimeInsideTimePeriod(time_t t1, time_t t2){
    time_t start = t2 - 60*60*24; //Removes 24h
    time_t stop = t2 + 60*60*24; //Adds 24h (but you already got it!)

    if(t1>=start && t1<=stop){
        return true;
    }
    return false;
}

double SensorService::distanceBetweenPositions(double latitudeA, double longitudeA, double latitudeB, double longitudeB){
    return sqrt(pow(latitudeB-latitudeA,2)+pow(longitudeB-longitudeA,2));
}

string SensorService::convertValuesAttributesToATMOScore(map<string,double> values){
    int  indexWorst = -1;
    int levelAtmo=-1;

    if(values["03"] != NULL) {
        if(values["O3"]>=0 && values["O3"]<=54){
            levelAtmo=1;
            
        }else if(values["O3"]>=55 && values["O3"]<=104){
            levelAtmo=2;
            
        }else if(values["O3"]>=105 && values["O3"]<=129){;
            levelAtmo=3;   
        }else if(values["O3"]>=130 && values["O3"]<=179){;
            levelAtmo=4;
        }else if(values["O3"]>=180 && values["O3"]<=239){;
            levelAtmo=5;
        }else{
            levelAtmo=6;
        }
        
        
        if(levelAtmo>=indexWorst){
            indexWorst=levelAtmo;
        }
    }
    
    if(values["SO2"] != NULL) {
        if(values["SO2"]>=0 && values["SO2"]<=79){
            levelAtmo=1;
            
        }else if(values["SO2"]>=80 && values["SO2"]<=159){
            levelAtmo=2;
            
        }else if(values["SO2"]>=160 && values["SO2"]<=199){;
            levelAtmo=3;   
        }else if(values["SO2"]>=200 && values["SO2"]<=299){;
            levelAtmo=4;
        }else if(values["SO2"]>=300 && values["SO2"]<=499){;
            levelAtmo=5;
        }else{
            levelAtmo=6;
        }
    
        if(levelAtmo>=indexWorst){
            indexWorst=levelAtmo;
        }
    }

    if(values["NO2"] != NULL) {
        if(values["NO2"]>=0 && values["NO2"]<=54){
            levelAtmo=1;
            
        }else if(values["NO2"]>=55 && values["NO2"]<=109){
            levelAtmo=2;
            
        }else if(values["NO2"]>=110 && values["NO2"]<=134){;
            levelAtmo=3;   
        }else if(values["NO2"]>=135 && values["NO2"]<=199){;
            levelAtmo=4;
        }else if(values["NO2"]>=200 && values["NO2"]<=399){;
            levelAtmo=5;
        }else{
            levelAtmo=6;
        }
        
        if(levelAtmo>=indexWorst){
            indexWorst=levelAtmo;
        }
    }

    if(values["PM10"] != NULL) {
        if(values["PM10"]>=0 && values["PM10"]<=54){
            levelAtmo=1;
            
        }else if(values["PM10"]>=55 && values["PM10"]<=109){
            levelAtmo=2;
            
        }else if(values["PM10"]>=110 && values["PM10"]<=134){;
            levelAtmo=3;   
        }else if(values["PM10"]>=135 && values["PM10"]<=199){;
            levelAtmo=4;
        }else if(values["PM10"]>=200 && values["PM10"]<=399){;
            levelAtmo=5;
        }else{
            levelAtmo=6;
        }
        
        if(levelAtmo>=indexWorst){
            indexWorst=levelAtmo;
        }
    }

    switch(indexWorst){
        case 1 :
            return "very good";
            break;
        case 2 :
            return "good";
            break;
        case 3 :
            return "average";
            break;
        case 4 :
            return "mediocre";
            break;
        case 5 :
            return "bad";
            break;
        case 6 :
            return "very bad";
            break;
        default :
            return "not computable";
            break;
    }
    
}


