#include <assert.h>
#include <iostream>
#include <string>

using namespace std;
#include "LoadService_test.h"

#define NDEBUG

void tests_LoadService();

int main()
{
    tests_LoadService();
    return 0;
}


void tests_LoadService() {
    LoadService_test loadServcie;

    string fileSensor = "res/test/sensors_test.csv";
    string file2 = "res/test/measurements_test.csv";
    string file3 = "res/test/attributes.csv";
    loadServcie.test_loadSensors(fileSensor,file2,file3);

    string file1 = "res/test/cleaners.csv";
    loadServcie.test_loadCleaners(file1);

    string fileUsers= "res/test/users.csv";
    string fileProviders= "res/test/providers.csv";
    string fileGovernment= "res/test/government.csv";
    string filePassword= "res/test/password.csv";
    loadServcie.test_loadUsers(fileUsers,fileProviders,fileGovernment,filePassword);
    
    cout<<"Test done"<<endl;

}

