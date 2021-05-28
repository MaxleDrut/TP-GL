#include "services/SensorService.h"

#include <map>


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
map<Attribute*, double> FR8_qualityAttributesExcludeSensor(
        double latitude, 
        double longitude, 
        time_t time, 
        Sensor& sensorToExclude
    ) {
    //TODO: modify the 


}

double FR5_malfunctioningAnalysis(Sensor sensorToCheck) {
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
double FR7_averageValue(
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
            (measurement->getTimestamp() > t1) &&
            (measurement->getTimestamp() < t2)
        ) {
            sum += measurement->getValue();
            checkedMeasurement++;
        }
    }
    return sum/checkedMeasurement;
}

map<Sensor, double, SensorComparator> FR7_sensorComparison(
        Sensor sensorToCompare, 
        time_t t1, 
        time_t t2
    ) {
    map<Sensor, double, SensorComparator> proximity;
    // TODO: finish function
    return proximity;
}


