#include <assert.h>
#include <iostream>
#include <string>

using namespace std;
#include "CleanerServices_test.h"
#include "SensorService_test.h"

#define NDEBUG

void tests_CleanersLoadCSV();
void tests_SensorService();

int main()
{
    //tests_CleanersLoadCSV();
    tests_SensorService();
    return 0;
}


void tests_SensorService() {
    SensorService_test SensServt;

    string fileSensor = "res/test/sensors.csv";
    
    SensServt.test_loadCSV(fileSensor);
    
    cout<<"Test done"<<endl;
}


void tests_CleanersLoadCSV(){
    CleanerServices_test * testsCleaners = new  CleanerServices_test();

    //Test avec la bonne file
    string file1 = "res/test/cleaners.csv";
    testsCleaners->test_loadCSV(file1);

    /*Test avec une mauvaise file
    string file2 = "aaaa.csv";
    testsCleaners->test_loadCSV(file2);*/

    delete(testsCleaners);
}