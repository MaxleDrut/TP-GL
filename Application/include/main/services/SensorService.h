#pragma once

#include <vector>
#include <string>
#include <map>
#include <time.h>
using namespace std;

#include "Attribute.h"
#include "Sensor.h"

class SensorService {
    public :
        bool loadCSV(string sensorFile, string measurementFile, string attributeFile);
        vector<Sensor> getSensors();
        Sensor getSensor(string identifier);
        double FR5_malfunctioningAnalysis(Sensor sensorToCheck);
        string FR8_quality(double latitude, double longitude, time_t time);
        
    private:
        map<Attribute,double> FR8_qualityAttributes(double latitude, double longitude, time_t time);
        bool isGivenTimeInsideTimePeriod(time_t start, time_t stop, time_t time);
        double distanceBetweenPositions(double latitudeA, double longitudeA, double latitudeB, double longitudeB);
        string convertValuesAttributesToATMOScore(map<Attribute,double> values);
        vector<Measurement> removeAllMeasurementsFromSensor(vector<Measurement> measurements, Sensor sensor);
        

};