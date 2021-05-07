#pragma once

#include <string>
#include <vector>
#include "sensors/Measurement.h"

using namespace std;

class Sensor
{
 private :
    string identifier;
    double latitude;
    double longitude;
    bool reliable;
    vector<Measurement> measurements{};

public:
    Sensor(string const &identifier, double latitude, double longitude, bool reliable, vector<Measurement> _measurements = vector<Measurement>())
    {
        this->identifier = identifier;
        this->latitude = latitude;
        this->longitude = longitude;
        this->reliable = reliable;
        this->measurements = move(_measurements);
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

    vector<Measurement> getMeasurements() const{
        return measurements;
    }

    void setReliable(bool isReliable){
        this->reliable = isReliable;
    }
};
