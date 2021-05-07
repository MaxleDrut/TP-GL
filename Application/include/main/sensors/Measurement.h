#pragma once

#include <string>
#include <ctime>
#include <memory>
#include "Sensor.h"

using namespace std;


class Measurement
{

    private :
        time_t timestamp;
        double value;
        unique_ptr<Sensor> sensor;

    public:

        Measurement(time_t const timestamp, double value, Sensor * sensor){
            this->timestamp = timestamp;
            this->value = value;
            this->sensor = sensor;
        }

        virtual ~Measurement(){
             delete sensor;
        }

        time_t getTimestamp () const{
            return timestamp;
        }

        double getValue() const{
            return value;
        }

        Sensor * getSensor() const{
            return sensor;
        }


};
