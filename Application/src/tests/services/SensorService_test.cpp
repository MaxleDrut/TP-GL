#include "SensorService_test.h"

int SensorService_test::test_loadCSV(string & file)
{
    SensorService sensor;

    sensor.loadCSV(file,file,file);

    vector<Sensor> lSensors = sensor.getSensors();

    for(Sensor s : lSensors) {
        cout<<s.getIdentifier()<<endl;
    }

    return 0;
}