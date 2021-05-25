#include <assert.h>
#include <string>

using namespace std;
#include "LoadService_test.h"
#include "UserService_test.h"
#include "SensorService_test.h"

#define NDEBUG

void tests_LoadService();
void tests_UserService();
void tests_SensorService();

int main()
{
    tests_LoadService();
    tests_UserService();
    tests_SensorService();
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

void tests_UserService(){
    UserService_test userService;

    string id = "Provider0";
    string pass = "provider0";
    userService.test_authentificate(id,pass);

    userService.test_getIndividualUsers();
    userService.test_getProviderUsers();
    userService.test_getPrivilege();

    cout<<"Test done"<<endl;
}


void tests_SensorService(){
    SensorService_test sensorService;

    
    sensorService.test_getSensors();
    sensorService.test_getSensor();

    cout<<"Test done"<<endl;
}
