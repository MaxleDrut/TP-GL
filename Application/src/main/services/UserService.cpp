//
// Created by onyr on 07/05/2021.
//

#include <vector>

#include "services/UserService.h"
#include "user/User.h"

using namespace std;

User UserService::authentificate(const string login, const string pass)
{
    // check if login exists in users
    for(User & user : this->users)
    {
        if(user.getIdentifier() == login)
        {
            if(user.getPassword() == pass) return user;
        }
    }
    
}

bool UserService::loadCSV (const string userFile, const string providerFile, const string governmentFile, const string passwordFile)
{
    ifstream fluxUser (userFile);
    ifstream fluxProvider (providerFile);
    ifstream fluxGovernment (governmentFile);
    ifstream fluxPassword (passwordFile);

    if(fluxPassword.is_open() && fluxUser.is_open() && fluxProvider.is_open() && fluxGovernment.is_open() ){
        string ligne;

        getline(fluxPassword,ligne);
        while(ligne!="\0"){
            int pos = 0;
            string id = loadInfo(ligne,pos);
            string password=loadInfo(ligne,pos);
            UserTypes usertype = getPrivilege(id);
            if(usertype==INDIVIDUAL){
                IndividualUser user (id,password);
                users.push_back(user);
            }else if(usertype == PROVIDER){
                ProviderUser user (id,password);
                users.push_back(user);
            }else if(usertype == GOVERNMENT){
                GovernmentUser user (id,password);
                users.push_back(user);
            }
            getline(fluxPassword,ligne);
        }


        fluxPassword.close();
        fluxUser.close();
        fluxProvider.close();
        fluxGovernment.close();
        return true;
    }
    return false;
}

string UserService::loadInfo(const string ligne, int & pos){

    string resultat;
    while(ligne[pos]!=';'){
        resultat+=ligne[pos];
        pos++;
    }
    pos++;
    return resultat;
}

UserTypes UserService::getPrivilege(const string identifier) const{
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
