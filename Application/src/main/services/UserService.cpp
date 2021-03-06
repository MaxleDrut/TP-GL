#include <vector>
#include <iostream>
#include "services/UserService.h"
#include "user/User.h"

using namespace std;

UserService::UserService(const vector<User *> &users){
    this->users = move(users);
}

UserService::~UserService(){}

User * UserService::authenticate(const string &login, const string &pass)
{
    // check if login exists in users
    for(auto &user : users)
    {
        if(user->getIdentifier().compare(login) == 0 && user->getPassword().compare(pass) == 0)
        {
            return user;
        }
    }
    return nullptr;
    
    return nullptr;
}

vector<IndividualUser *> UserService::getIndividualUsers () const{
    
    vector<IndividualUser *> individuals;

    // check if login exists in users
    for(User * user : this->users)
    {
        if(getPrivilege(user->getIdentifier()) == INDIVIDUAL)
        {
            individuals.push_back(static_cast<IndividualUser *>(user) );
        }
    }

    const vector<IndividualUser *> individuals2 = move(individuals);
    return individuals2;
}


vector<ProviderUser *> UserService::getProviderUsers () const{
    
    vector<ProviderUser *> providers;

    // check if login exists in users
    for(User * user : this->users)
    {
        if(getPrivilege(user->getIdentifier()) == PROVIDER)
        {
            providers.push_back(static_cast<ProviderUser *>(user) );
        }
    }

    const vector<ProviderUser *> providers2 = move(providers);
    return providers2;
}

UserTypes UserService::getPrivilege(const string identifier) const{
    string id = identifier.substr(0,identifier.size()-1);
    if(id=="User"){
        return UserTypes::INDIVIDUAL;
    }else if(id=="Provider"){
        return UserTypes::PROVIDER;
    }else if(id=="Government"){
        return UserTypes::GOVERNMENT;
    }
    return UserTypes::NONE;
}

vector<User *> UserService::getUsers() const 
{
    return users;
}
