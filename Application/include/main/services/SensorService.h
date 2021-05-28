#pragma once

#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <fstream>
#include "sensors/Attribute.h"
#include "sensors/Sensor.h"

using namespace std;

class SensorService {
    private :
        vector<Sensor *> sensors;
        vector<Attribute *> attributes;

        int start;
        int end;
    public :
        SensorService() = default;
        SensorService(vector<Attribute *> attributes, vector<Sensor *> sensors);
        virtual ~SensorService() = default;

        vector<Sensor *> getSensors();
        vector<Attribute *> getAttributes();
        Sensor * getSensor(string identifier);
        double FR5_malfunctioningAnalysis(Sensor sensorToCheck);
        string FR8_quality(double latitude, double longitude, time_t time);
        map<Sensor,double, SensorComparator> FR7_sensorComparison(Sensor sensorToCompare, time_t t1, time_t t2);
        
    private:
        map<Attribute,double> FR8_qualityAttributes(double latitude, double longitude, time_t time);
        map<Attribute*, double> FR8_qualityAttributesExcludeSensor(
            double latitude, 
            double longitude, 
            time_t time, 
            Sensor& sensorToExclude
        );
        bool isGivenTimeInsideTimePeriod(time_t start, time_t stop, time_t time);
        double distanceBetweenPositions(double latitudeA, double longitudeA, double latitudeB, double longitudeB);
        string convertValuesAttributesToATMOScore(map<Attribute,double> values);
        vector<Measurement *> removeAllMeasurementsFromSensor(vector<Measurement *> measurements, Sensor sensor);

};