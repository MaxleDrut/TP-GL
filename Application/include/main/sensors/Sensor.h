#pragma once

#include <string>
#include <vector>
#include "Measurement.h"

using namespace std;


class Sensor
{
     private :
        string identifier;
        double latitude;
        double longitude;
        bool reliable;
        vector<Measurement> measurements;

    public:

        Sensor(string const identifier, double latitude,double longitude, bool reliable, vector<Measurement> measurements){
            this->identifier = identifier;
            this->latitude = latitude;
            this->longitude = longitude;
            this->reliable = reliable;
            this->measurements = move(measurements);
        }

        virtual ~Sensor(){
            delete measurements;
        }

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

        void setReliable(bool reliable){
            this->reliable = reliable;
        }



};
