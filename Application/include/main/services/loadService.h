#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "services/UserService.h"
#include "user/Cleaner.h"
#include "user/User.h"
#include "user/IndividualUser.h"
#include "user/GovernmentUser.h"
#include "user/ProviderUser.h"
#include "sensors/Attribute.h"
#include "sensors/Measurement.h"
#include "sensors/Sensor.h"

using namespace std;

class LoadService
{


    private:
        vector<Cleaner *> cleaners;
        vector<User *> users;
        vector<Sensor *> sensors;
        vector<Attribute *> attributes;
        vector<Measurement *> measurements;

        string loadInfo(const string ligne, int & pos);
        UserTypes getPrivilege(const string identifier) const;

    public:
        LoadService();
        virtual ~LoadService();

        bool loadCSV(string & userFile, string & providerFile, string & governmentFile, string & passwordFile, string & cleanersFile, string & sensorsFile, string & measurementFile, string & attributeFile);
        bool loadCleaners(string  & file);
        bool loadSensors(string & sensorFile, string & measurementFile, string & attributeFile);
        bool loadUsers(const string userFile, const string providerFile, const string governmentFile, const string passwordFile);

        vector<Cleaner *> getCleaners();
        vector<User *> getUsers();
        vector<Sensor *> getSensors();
        vector<Attribute *> getAttributes();
        vector<Measurement *> getMeasurements();

};