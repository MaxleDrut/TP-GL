#include "AlgosSpeedTest.h"

AlgosSpeedTest::AlgosSpeedTest() {
    LoadService loadService;
    string fileSensor = "res/dataset/sensors.csv";
    string file2 = "res/dataset/measurements.csv";
    string file3 = "res/dataset/attributes.csv";
    loadService.loadSensors(fileSensor,file2,file3);
    vector<Sensor *> sensors = loadService.getSensors();
    vector<Attribute *> attributes = loadService.getAttributes();

    service = new SensorService(attributes,sensors);
}

AlgosSpeedTest::~AlgosSpeedTest() {
    delete service;
}


void AlgosSpeedTest::perf_FR8_AirQuality() {

    cout<<"Starting FR8_AirQuality()"<<endl<<"Input : Coordinates = 45,0 | Time = 2019-02-19 13:00:00"<<endl;
    
    string date= "2019-02-19  13:00:00";
    tm requestTimeDate = {};
    istringstream rqTimeStreamDate(date);
    rqTimeStreamDate >> get_time(&requestTimeDate, "%Y-%m-%d% %H:%M:%S");

    auto start = chrono::high_resolution_clock::now();

    auto time = mktime(&requestTimeDate);
    string output = service->FR8_quality(45,0,time);

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    
    cout<<"Output : "<<output<<endl;
    cout<<"Duration : "<<elapsed.count()<<"s"<<endl;
    cout<<"End of FR8_AirQuality()"<<endl;
}

void AlgosSpeedTest::perf_FR5_Malfunction() {
    cout<<"Starting FR5_Malfunction()"<<endl<<"Input : Sensor0"<<endl;
    
    Sensor * s0 = service->getSensor("Sensor0");

    auto start = chrono::high_resolution_clock::now();

    double output = service->FR5_malfunctioningAnalysis(*s0);

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    
    cout<<"Output : "<<output*100<<"% of likeliness of malfunction"<<endl;
    cout<<"Duration : "<<elapsed.count()<<"s"<<endl;   
    cout<<"End of FR5_Malfunction()"<<endl;
}

void AlgosSpeedTest::perf_FR7_SensorComparison() {

    cout<<"Starting FR7_SensorComparison()"<<endl<<"Input : SensorToCompare = Sensor0 | Start = 2019-02-01 00:00:00 | End = 2019-03-01 00:00:00"<<endl;
    
    Sensor * s0 = service->getSensor("Sensor0");
    string d1= "2019-02-01  00:00:00";
    tm t1 = {};
    istringstream rqTime1(d1);
    rqTime1 >> get_time(&t1, "%Y-%m-%d% %H:%M:%S");

    string d2= "2019-03-01  00:00:00";
    tm t2 = {};
    istringstream rqTime2(d2);
    rqTime2 >> get_time(&t2, "%Y-%m-%d% %H:%M:%S");

    auto start = chrono::high_resolution_clock::now();

    auto time_start = mktime(&t1);
    auto time_stop = mktime(&t2);
    map<Sensor,double, SensorComparator> output = service->FR7_sensorComparison(*s0,time_start,time_stop);

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    cout<<"Output : "<<endl;
    for(auto &it : output) {
        cout<<it.first.getIdentifier()<<" : "<<it.second*100<<"%"<<endl;
    }
    cout<<"Duration : "<<elapsed.count()<<"s"<<endl;
    cout<<"End of FR7_SensorComparison()"<<endl;
}