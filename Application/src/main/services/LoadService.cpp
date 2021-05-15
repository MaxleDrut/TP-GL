#include <iomanip>
#include <sstream>
#include <iostream>
#include "services/LoadService.h"
using namespace std;


LoadService::LoadService(){

}

LoadService::~LoadService(){}


bool LoadService::loadCSV(string & userFile, string & providerFile, string & governmentFile, string & passwordFile, string & cleanersFile, string & sensorsFile, string & measurementFile, string & attributeFile){
    bool loadSensor = loadSensors(sensorsFile,measurementFile,attributeFile);
    bool loadCleaner = loadCleaners(cleanersFile);
    bool loadUser = loadUsers(userFile,providerFile,governmentFile,passwordFile);

    if(loadSensor && loadCleaner && loadUser){
        return true;
    }

    return false;
}

bool LoadService::loadCleaners(string & file){
    ifstream flux (file);
    string line;

    if(flux.is_open()){
        getline(flux,line);
        while(line!="\0"){
            int pos = 0;
            string id = loadInfo(line,pos);
            string latitude = loadInfo(line,pos);
            string longitude = loadInfo(line,pos);
            string start =loadInfo(line,pos);
            string stop = loadInfo(line,pos);
            
            tm requestTimeStart = {};
            istringstream rqTimeStreamStart(start);
            rqTimeStreamStart >> get_time(&requestTimeStart, "%Y-%m-%d% %H:%M:%S");
            tm requestTimeStop = {};
            istringstream rqTimeStreamStop(stop);
            rqTimeStreamStop >> get_time(&requestTimeStop, "%Y-%m-%d% %H:%M:%S");

           
            cleaners.push_back(new Cleaner(id,stof(latitude),stof(longitude),mktime(&requestTimeStart),mktime(&requestTimeStop)));
            getline(flux,line);
        }
        
        flux.close();
        return true;
    }
    
    return false;
    
}


bool LoadService::loadSensors(string & sensorFile, string & measurementFile, string & attributeFile) {
    ifstream fluxSensor (sensorFile);
    ifstream fluxMeasurement (measurementFile);
    ifstream fluxAttribute (attributeFile);
    string line;

    if(fluxSensor.is_open() &&  fluxMeasurement.is_open() && fluxAttribute.is_open()){

        //Attributes 
        getline(fluxAttribute,line);
        while(line!="\0") {
            int pos=0;
            string id = loadInfo(line,pos);
            string unit = loadInfo(line,pos);
            string description = loadInfo(line,pos);
            attributes.push_back(new Attribute(unit,description,id));
            
            getline(fluxAttribute,line);
        }

       
       //Sensors
        getline(fluxSensor,line);
        while(line!="\0") {
            int pos=0;
            string id = loadInfo(line,pos);
            string latitude = loadInfo(line,pos);
            string longitude = loadInfo(line,pos);

            sensors.push_back(new Sensor(id,stof(latitude),stof(longitude),true));

            getline(fluxSensor,line);
        }

        
        //Measurements
        getline(fluxMeasurement,line);
        while(line!="\0") {
            int pos=0;
            string date = loadInfo(line,pos);
            string sensorId = loadInfo(line,pos);
            string attributeId= loadInfo(line,pos);
            string value = loadInfo(line,pos);

            tm requestTimeDate = {};
            istringstream rqTimeStreamDate(date);
            rqTimeStreamDate >> get_time(&requestTimeDate, "%Y-%m-%d% %H:%M:%S");
            
            for(int i =0 ; i<attributes.size(); i++){
                if(attributeId==attributes[i]->getIdentifier()){
                   measurements.push_back(new Measurement(mktime(&requestTimeDate),stof(value),attributes[i], nullptr));
                }
            }

            for(int i =0 ; i<sensors.size(); i++){
                if(sensorId==sensors[i]->getIdentifier()){
                   measurements[measurements.size()-1]->setSensor(sensors[i]);
                   sensors[i]->addMeasurement(measurements[measurements.size()-1]);
                }
            }
            
            getline(fluxMeasurement,line);
        }

        fluxAttribute.close();
        fluxMeasurement.close();
        fluxSensor.close();


        return true;
    }
    return false;
   

}


bool LoadService::loadUsers (const string userFile, const string providerFile, const string governmentFile, const string passwordFile)
{
    ifstream fluxUser (userFile);
    ifstream fluxProvider (providerFile);
    ifstream fluxGovernment (governmentFile);
    ifstream fluxPassword (passwordFile);

    if(fluxPassword.is_open() && fluxUser.is_open() && fluxProvider.is_open() && fluxGovernment.is_open() ){
        string line;

        //Password and login
        getline(fluxPassword,line);
        while(line!="\0"){
            int pos = 0;
            string id = loadInfo(line,pos);
            string password=loadInfo(line,pos);
            UserTypes usertype = getPrivilege(id);
            
            if(usertype==INDIVIDUAL){
                //IndividualUser user (id,password);
                users.push_back(new IndividualUser(id,password));
            }else if(usertype == PROVIDER){
                //ProviderUser user (id,password);
                users.push_back(new ProviderUser(id,password));
            }else if(usertype == GOVERNMENT){
               // GovernmentUser user (id,password);
                users.push_back(new GovernmentUser(id,password));
            }
            getline(fluxPassword,line);
        }

        //Individual Users
        getline(fluxUser,line);
        while(line!="\0"){
            int pos=0;
            string id = loadInfo(line,pos);
            string sensorId = loadInfo(line,pos);
            for(int i =0; i<users.size() ; i++){
                if(users[i]->getIdentifier() == id){
                    for(int j=0; j<sensors.size(); j++){
                        if(sensorId==sensors[j]->getIdentifier()){
                            (static_cast<IndividualUser *>(users[i]))->addSensor(sensors[j]);
                        }
                    }
                }
            }
            getline(fluxUser,line);
        }

        
        //Provider Users
        getline(fluxProvider,line);
        while(line!="\0"){
            int pos=0;
            string id = loadInfo(line,pos);
            string cleanerId = loadInfo(line,pos);
            for(int i =0; i<users.size() ; i++){
                if(users[i]->getIdentifier() == id){
                    for(int j=0; j<cleaners.size(); j++){
                        if(cleanerId==cleaners[j]->getIdentifier()){
                            (static_cast<ProviderUser *>(users[i]))->addCleaner(cleaners[j]);
                        }
                    }
                }
            }
            getline(fluxProvider,line);
        }

        fluxPassword.close();
        fluxUser.close();
        fluxProvider.close();
        fluxGovernment.close();
        return true;
    }
    return false;
}


vector<Cleaner *> LoadService::getCleaners(){
    return cleaners;
}

vector<User *> LoadService::getUsers(){
    return users;
}

vector<Sensor *> LoadService::getSensors(){
    return sensors;
}

vector<Attribute *> LoadService::getAttributes(){
    return attributes;
}

vector<Measurement *> LoadService::getMeasurements(){
    return measurements;
}

string LoadService::loadInfo(const string line, int & pos){

    string resultat;
    char tiret = line[pos];
    while(line[pos]!=';' && line[pos]!='\0'){
        resultat+=line[pos];
        pos++;
    }
    pos++;
    return resultat;
}

UserTypes LoadService::getPrivilege(const string identifier) const{
    string id = identifier.substr(0,identifier.size()-1);
    if(id=="User"){
        return INDIVIDUAL;
    }else if(id=="Provider"){
        return PROVIDER;
    }else if(id=="Government"){
        return GOVERNMENT;
    }
    return AUCUN;
}