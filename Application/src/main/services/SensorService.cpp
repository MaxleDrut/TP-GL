#include "services/SensorService.h"


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

