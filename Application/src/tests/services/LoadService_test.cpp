#include "LoadService_test.h"

LoadService_test::LoadService_test(){
    load = new LoadService();
}

LoadService_test::~LoadService_test(){
    delete load;
}

int LoadService_test::test_loadCleaners(string & file){

    string badFile = "baba.csv";
    bool res2 = load->loadCleaners(badFile);
    assert(res2==false);
    
    bool res = load->loadCleaners(file);
    assert(res==true);

    vector<Cleaner *> lcleaners = load->getCleaners();
    assert(lcleaners.size()==2);

    cout << "Cleaners successfully loaded" <<endl;

    return 0;
}

int LoadService_test::test_loadSensors(string & file1, string & file2, string & file3)
{

    string badFile = "baba.csv";
    bool res2 = load->loadSensors(badFile,file1,file2);
    assert(res2==false);

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

    bool res2 = load->loadUsers("baba.csv",providerFile,governmentFile,passwordFile);
    assert(res2==false);

    cout << "Users successfully loaded" <<endl;

    return 0;
}