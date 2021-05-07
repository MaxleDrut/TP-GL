#include "SensorService.h"

bool SensorService::loadCSV(string sensorFile, string measurementFile, string attributeFile) {
    string line = "";

    //Lecture des Sensors
    ifstream fluxSensor;
    fluxSensor.open(sensorFile);

    if(!fluxSensor) {
        return false;
    }
    while(line!="\0") {
        getline(fluxSensor,line);
        start = end = 0;
        sensors.push_back(Sensor(readUntilSemicolon(line),stof(readUntilSemicolon(line)),stof(readUntilSemicolon(line)),true));
    }

    //Lecture des attributs
    line = "";
    ifstream fluxAttribute;
    fluxAttribute.open(attributeFile);

    if(!fluxAttribute) {
        return false;
    }
    while(line!="\0") {
        getline(fluxSensor,line);
        start = end = 0;
        attributes.push_back(Attribute(readUntilSemicolon(line),readUntilSemicolon(line),readUntilSemicolon(line)));
    }

    //Lecture des Measurements
   

}

//Allows to read an attribute by returning the substring until the next ;
string SensorService::readUntilSemicolon(string input) {
    string output;
    while(input[end] != ';' && end<100) {
        end++;
    }

    if(end == 100) {
        output = "";
    } else {
        output = input.substr(start,(end-start-1));
        end++;
        start = end;
    }

    return output;

    
}