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

    cout<<"Test stored sensors ok"<<endl;

    return 0;
 
}

int SensorService_test::test_getSensor(){
    Sensor * sensor = service->getSensor("Sensor0");
    assert(sensor->getIdentifier()=="Sensor0");
    assert(sensor->getLatitude()==44);
    assert(sensor->getLongitude()==-1);

    Sensor * sensor2 = service->getSensor("Sensor101");
    assert(sensor2==nullptr);

    cout<<"Test get a specified sensor ok"<<endl;

    return 0;
 
}

int SensorService_test::test_isGivenTimeInsideTimePeriod(){
    string date= "2019-01-01  12:00:00";
    tm requestTimeDate = {};
    istringstream rqTimeStreamDate(date);
    rqTimeStreamDate >> get_time(&requestTimeDate, "%Y-%m-%d% %H:%M:%S");
    bool res = service->isGivenTimeInsideTimePeriod(mktime(&requestTimeDate)+60*20,mktime(&requestTimeDate));
    assert(res==true);

    
    string time= "2025-01-01  12:00:00";
    tm requestTime = {};
    istringstream rqTimeStreamTime(time);
    rqTimeStreamTime>> get_time(&requestTime, "%Y-%m-%d% %H:%M:%S");
    bool res2 = service->isGivenTimeInsideTimePeriod(mktime(&requestTimeDate),mktime(&requestTime));
    assert(res2==false);

    cout<<"Test time in period ok"<<endl;

    return 0;


}

int SensorService_test::test_distanceBetweenPositions(){
    double distance = service->distanceBetweenPositions(44,-1,45,-2);

    //Little trick to round the number to two digits (but C++ doesn't handle its precise value properly...)
    distance = ((int)(distance*100))/100.0;

    //The expected value is 1.41, with a precision of a least 3 digits.
    assert(distance - 1.41 <0.001);

    cout<<"Test distance calculation ok"<<endl;
    return 0;
}

int SensorService_test::test_FR8_qualityAttributes() {
    string date= "2019-01-01  12:00:00";
    tm requestTimeDate = {};
    istringstream rqTimeStreamDate(date);
    rqTimeStreamDate >> get_time(&requestTimeDate, "%Y-%m-%d% %H:%M:%S");

    map<Attribute *,double> output = service->FR8_qualityAttributes(45,-2,mktime(&requestTimeDate));

    double expectedValues[4] = {55.59,38.54,69.24,47.41};
    int i=0;

    for(auto &it : output) {
        double round = ((int)(it.second*100))/100.0;
        assert(round-expectedValues[i] < 0.001);
        i++;
    }

    string date2= "2025-01-01  12:00:00";
    tm requestTimeDate2 = {};
    istringstream rqTimeStreamDate2(date2);
    rqTimeStreamDate2 >> get_time(&requestTimeDate2, "%Y-%m-%d% %H:%M:%S");

    map<Attribute *,double> output2 = service->FR8_qualityAttributes(45,-2,mktime(&requestTimeDate2));

    double expectedValues2[4] = {NULL,NULL,NULL,NULL};
    i=0;
    for(auto &it : output2) {
        double round = ((int)(it.second*100))/100.0;
        assert(round-expectedValues[i] < 0.001);
        i++;
    }

    cout<<"Test FR8_qualityAttributes ok"<<endl;
    return 0;

}

int SensorService_test::test_FR8_quality(){
    string date= "2019-01-01  12:00:00";
    tm requestTimeDate = {};
    istringstream rqTimeStreamDate(date);
    rqTimeStreamDate >> get_time(&requestTimeDate, "%Y-%m-%d% %H:%M:%S");
    auto time = mktime(&requestTimeDate);

    string val = service->FR8_quality(45,-2,time);
    assert(val=="good");

    string date2= "2025-01-01  12:00:00";
    tm requestTimeDate2 = {};
    istringstream rqTimeStreamDate2(date2);
    rqTimeStreamDate2 >> get_time(&requestTimeDate2, "%Y-%m-%d% %H:%M:%S");
    time = mktime(&requestTimeDate2);

    string val2 = service->FR8_quality(45,-2,time);
    assert(val2=="not computable");

    cout<<"Test FR8_quality ok"<<endl;
    return 0;
}

int SensorService_test::test_convertValuesAttributesToATMOScore(){
    map<string,double> values;
    values.insert(pair<string,double>("O3",55.56));
    values.insert(pair<string,double>("NO2",69.28));
    values.insert(pair<string,double>("SO2",38.56));
    values.insert(pair<string,double>("PM10",47.39));

    string res = service->convertValuesAttributesToATMOScore(values);
    assert(res=="good");

    cout<<"Test conversion ok"<<endl;
    
    return 0;
}

//Finds the sensor identified "Sensor0" and runs the malfunctionning analysis
int SensorService_test::test_FR5_malfunctioningAnalysis(){
    Sensor * sens = service->getSensor("Sensor0");
    double res = service->FR5_malfunctioningAnalysis(*sens);
    //The expected value is 0.184, with a precision of at least 3 digits
    assert((((int)(res*100))/100.0)-0.184<0.001);
        
     
    cout<<"Test FR5_malfunctioningAnalysis ok"<<endl;

    return 0;
}


int SensorService_test::test_FR7_averageValue() {
    //for the 1rst test, we have to find the sensor "Sensor0", the attribute "O3" and define the dates 
    string date= "2019-01-01  12:00:00";
    tm requestTimeDate = {};
    istringstream rqTimeStreamDate(date);
    rqTimeStreamDate >> get_time(&requestTimeDate, "%Y-%m-%d% %H:%M:%S");

    Sensor * sens = service->getSensor("Sensor0");
        for(auto &att : service->getAttributes()) {
            if(att->getIdentifier()=="O3") {
                double res = service->FR7_averageValue(*sens,*att,mktime(&requestTimeDate),mktime(&requestTimeDate)+60*20);
                //The expected value is 50.25., with a precision of at least 3 digits
                assert((((int)(res*100))/100.0)-50.25<0.001);
            }
        }

    //For the 2nd test, we create a bad attribute "o2" and expect a null value (instead of a crash)
    string unit = "us dollars";
    string description ="we use it to breathe, and it's cool";
    string id = "o2";
    Attribute o2(unit,description,id);
            
    double res = service->FR7_averageValue(*sens,o2,mktime(&requestTimeDate),mktime(&requestTimeDate)+60*20);
    assert(res == NULL);

    cout<<"Test FR7_averageValue ok"<<endl;
    return 0;
}

int SensorService_test::test_FR7_sensorComparison() {
    string date= "2019-01-01  12:00:00";
    tm requestTimeDate = {};
    istringstream rqTimeStreamDate(date);
    rqTimeStreamDate >> get_time(&requestTimeDate, "%Y-%m-%d% %H:%M:%S");

    Sensor * s0 = service->getSensor("Sensor0");
    auto start = mktime(&requestTimeDate);
    auto end = start +20*60;

    map<Sensor,double,SensorComparator> res = service->FR7_sensorComparison(*s0, start, end);

    //The map must contain one row : 'Sensor1 - 0.846'
    assert(res.size()==1);
    Sensor * s1 = service->getSensor("Sensor1");
    double val = res[*s1];
    assert((((int)(val*1000))/1000.0)-0.846<0.0001);

    //Create a fake sensor "Sensor101" not in the DataBase
    string id = "Sensor101";
    Sensor fakeSensor(id,42,69,true);
    auto time = mktime(&requestTimeDate);
    auto time2 = time+20*60;

    map<Sensor,double,SensorComparator> res2 = service->FR7_sensorComparison(fakeSensor, time, time2);
    //The map must be empty
    assert(res2.size()==0);

    cout<<"Test FR7_sensorComparison ok"<<endl;

    return 0;
}

