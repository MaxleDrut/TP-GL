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

    vector<Cleaner *> lcleaners = load->getCleaners();
    assert(lcleaners.size()==2);

    cout << "Cleaners successfully loaded" <<endl;

    return 0;
}

int LoadService_test::test_loadSensors(string & file1, string & file2, string & file3)
{
    bool res = load->loadSensors(file1,file2,file3);
    assert(res==true);

    vector<Sensor *> lSensors = load->getSensors();
    assert(lSensors.size()==2);
    
    vector<Measurement *> lMeasurements = load->getMeasurements();
    assert(lMeasurements.size()==8);

    cout << "Sensors successfully loaded" <<endl;

    return 0;
}


int LoadService_test::test_loadUsers(string & userFile, string & providerFile, string & governmentFile, string & passwordFile)
{
    bool res = load->loadUsers(userFile,providerFile,governmentFile,passwordFile);
    assert(res==true);

    vector<User *> lUsers = load->getUsers();
    assert(lUsers.size()==6);

    for(int i=0; i<lUsers.size(); i++){
        assert(!lUsers[i]->getIdentifier().empty());
        assert(!lUsers[i]->getPassword().empty());

    }

    

    cout << "Users successfully loaded" <<endl;

    return 0;
}