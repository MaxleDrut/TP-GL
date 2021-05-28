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

    //Little trick to round the number to two digits
    distance = ((int)(distance*100))/100.0;

    assert(distance - 1.41 <0.001);

    cout<<"test distance ok"<<endl;
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
        double arrondi = ((int)(it.second*100))/100.0;
        assert(arrondi-expectedValues[i] < 0.001);
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
        double arrondi = ((int)(it.second*100))/100.0;
        assert(arrondi-expectedValues[i] < 0.001);
        i++;
    }

    cout<<"test fr8 quality attributes ok"<<endl;
    return 0;

}

int SensorService_test::test_FR8_quality(){
    string date= "2019-01-01  12:00:00";
    tm requestTimeDate = {};
    istringstream rqTimeStreamDate(date);
    rqTimeStreamDate >> get_time(&requestTimeDate, "%Y-%m-%d% %H:%M:%S");

    string val = service->FR8_quality(45,-2,mktime(&requestTimeDate));
    assert(val=="good");

    string date2= "2025-01-01  12:00:00";
    tm requestTimeDate2 = {};
    istringstream rqTimeStreamDate2(date2);
    rqTimeStreamDate2 >> get_time(&requestTimeDate2, "%Y-%m-%d% %H:%M:%S");

    string val2 = service->FR8_quality(45,-2,mktime(&requestTimeDate2));
    assert(val2=="not computable");

    cout<<"test fr8 quality ok"<<endl;
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

    cout<<"test conversion ok"<<endl;
    
    return 0;
}

