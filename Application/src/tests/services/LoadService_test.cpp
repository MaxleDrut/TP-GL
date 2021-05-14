#include "LoadService_test.h"

LoadService_test::LoadService_test(){
    load = new LoadService();
}

LoadService_test::~LoadService_test(){
    delete load;
}

int LoadService_test::test_loadCleaners(string & file){
    
    bool res = load->loadCleaners(file);
    assert(res==true);
    vector<Cleaner> cleaners = load->getCleaners();
    cout << "Le test est réussi" <<endl;

    return 0;
}

int LoadService_test::test_loadSensors(string & file1, string & file2, string & file3)
{
    load->loadSensors(file1,file2,file3);

    vector<Measurement> measurements = load->getMeasurements();
    cout<<measurements.size()<<endl;
    for(Measurement s : measurements) {
        cout<<s.getValue()<<endl;
    }
    
    vector<Sensor> lSensors = load->getSensors();
    cout<<lSensors.size()<<endl;
    for(Sensor s : lSensors) {
        cout<<s.getIdentifier()<<endl;
    }

    return 0;
}