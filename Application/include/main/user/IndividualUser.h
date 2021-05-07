#pragma once

#include <string>
#include <vector>

#include "User.h"
#include "Sensor.h"

using namespace std;


class IndividualUser: User
{

private:
    vector<Sensor> sensors;
    
public:

    IndividualUser(string identifier, string password)
    {
        this->identifier = identifier;
        this->password = password;
    }

    virtual ~IndividualUser()
    {
        
    }

    vector<Sensor> getSensors()
    {
        return this->sensors;
    }

    void addSensor(Sensor sensor)
    {
        this->sensors.push_back(sensor);
    }

};
