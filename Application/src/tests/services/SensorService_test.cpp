#include "SensorService_test.h"

using namespace std;

SensorService_test::SensorService_test(){
    LoadService loadService;
    string fileSensor = "res/test/sensors_test.csv";
    string file2 = "res/test/measurements_test.csv";
    string file3 = "res/test/attributes.csv";
    loadService.loadSensors(fileSensor,file2,file3);
    vector<Sensor *> sensors = loadService.getSensors();
    vector<Attribute *> attributes = loadService.getAttributes();
    service = new SensorService(attributes,sensors);
}

SensorService_test::~SensorService_test(){
    delete service;
}

int SensorService_test::test_getSensors(){
    const vector<Sensor *> sensors = service->getSensors();
    assert(sensors[0]->getIdentifier()=="Sensor0");
    assert(sensors[1]->getIdentifier()=="Sensor1");

    cout<<"Valid sensors"<<endl;

    return 0;
 
}

int SensorService_test::test_getSensor(){
    Sensor * sensor = service->getSensor("Sensor0");
    assert(sensor->getIdentifier()=="Sensor0");
    assert(sensor->getLatitude()==44);
    assert(sensor->getLongitude()==-1);

    Sensor * sensor2 = service->getSensor("Sensor101");
    assert(sensor2==nullptr);

    cout<<"Valid sensor"<<endl;

    return 0;
 
}

int SensorService_test::test_FR5_malfunctioningAnalysis() {
    
    return 0;
}
