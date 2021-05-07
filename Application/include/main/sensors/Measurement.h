#pragma once

#include <string>
#include <ctime>
#include <memory>
#include "sensors/Sensor.h"
#include "sensors/Attribute.h"

using namespace std;

class Sensor;

class Measurement
{
private :
    time_t timestamp;
    double value;
    Attribute *attribute;
    Sensor *sensor;

public:
    Measurement(time_t timestamp, double value, Attribute *attr, Sensor *sens)
    {
        this->timestamp = timestamp;
        this->value = value;
        this->sensor = sens;
        this->attribute = attr;
    }

    virtual ~Measurement() = default;

    time_t getTimestamp() const
    {
        return timestamp;
    }

    double getValue() const
    {
        return value;
    }

    Sensor * getSensor() const
    {
        return sensor;
    }

    Attribute * getAttribute() const
    {
        return attribute;
    }
};
