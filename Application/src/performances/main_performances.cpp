#include <assert.h>
#include <string>

using namespace std;

#include "AlgosSpeedTest.h"

void callSpeedTests();

int main()
{
    callSpeedTests();    
    return 0;
}

void callSpeedTests() {
    cout<<"----- | Starting SpeedTests | -----"<<endl;
    cout<<"-----------------------------------"<<endl<<endl;

    AlgosSpeedTest speedTest;
    speedTest.perf_FR8_AirQuality();
    cout<<endl;
    speedTest.perf_FR5_Malfunction();
    cout<<endl;
    speedTest.perf_FR7_SensorComparison();

    cout<<endl<<"---------------------------------"<<endl;
    cout<<"----- | End of SpeedTests | -----"<<endl;
}


