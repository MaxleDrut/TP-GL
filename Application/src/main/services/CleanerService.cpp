

#include <sstream>
#include <iomanip>
#include "services/CleanerService.h"
using namespace std;

CleanerService::CleanerService(){}

CleanerService::~CleanerService(){}

bool CleanerService::loadCSV(string & file){
    ifstream flux (file);
    string ligne;

    if(flux.is_open()){
        getline(flux,ligne);
        while(ligne!="\0"){
            int pos = 0;
            string id;
            while(ligne[pos]!=';'){
                id+=ligne[pos];
                pos++;
            }

            pos++;
            string latitude;
            while(ligne[pos]!=';'){
                latitude+=ligne[pos];
                pos++;
            }

            pos++;
            string longitude;
            while(ligne[pos]!=';'){
                longitude+=ligne[pos];
                pos++;
            }

            pos++;
            string start;
            while(ligne[pos]!=';'){
                start+=ligne[pos];
                pos++;
            }

            pos++;
            string stop;
            while(ligne[pos]!=';'){
                stop+=ligne[pos];
                pos++;
            }
            tm requestTimeStart = {};
            istringstream rqTimeStreamStart(start);
            rqTimeStreamStart >> get_time(&requestTimeStart, "%Y-%m-%d% %H:%M:%S");

            tm requestTimeStop = {};
            istringstream rqTimeStreamStop(stop);
            rqTimeStreamStop >> get_time(&requestTimeStop, "%Y-%m-%d% %H:%M:%S");

            Cleaner cleaner (id,stof(latitude),stof(longitude),mktime(&requestTimeStart),mktime(&requestTimeStop));
            cleaners.push_back(cleaner);
        }

        return true;
    }else{
        return false;
    }
    
}


vector<Cleaner> CleanerService::getCleaners() const{
    return cleaners;
}