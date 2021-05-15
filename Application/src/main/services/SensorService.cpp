#include "services/SensorService.h"

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

