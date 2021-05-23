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

/*Sensor getSensor(string identifier) {
    /*for(vector<Sensor>::iterator it = sensors.begin(); it!=sensors.end(); it++) {

    }
   
}*/

