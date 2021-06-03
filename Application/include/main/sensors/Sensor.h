#pragma once

#include <string>
#include <vector>
#include "sensors/Measurement.h"

using namespace std;

class Measurement;

class Sensor
{
 private :
    string identifier;
    double latitude;
    double longitude;
    bool reliable;
    vector<Measurement *> measurements{};

public:
    Sensor(string const &identifier, double latitude, double longitude, bool reliable)
    {
        this->identifier = identifier;
        this->latitude = latitude;
        this->longitude = longitude;
        this->reliable = reliable;
    }

    virtual ~Sensor()= default;

    string getIdentifier () const{
        return identifier;
    }

    double getLatitude() const{
        return latitude;
    }

    double getLongitude() const{
        return longitude;
    }

    bool getReliable() const{
        return reliable;
    }

    vector<Measurement *> getMeasurements() const{
        return measurements;
    }

    void setReliable(bool isReliable){
        this->reliable = isReliable;
    }

    void addMeasurement(Measurement  * measurement){
        this->measurements.push_back(measurement);
    }
};

class SensorComparator
{
public:
    bool operator() (const Sensor &s1, const Sensor &s2) const {
        return s1.getIdentifier() < s2.getIdentifier();
    }
    // ex: map<Sensor, double, SensorComparator> mapSensorDouble;
};


