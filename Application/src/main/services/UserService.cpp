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
