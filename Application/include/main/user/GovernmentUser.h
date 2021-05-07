#pragma once

#include <string>
#include "User.h"

using namespace std;


class GovernmentUser: User
{
    
public:

    GovernmentUser(string identifier, string password)
    {
        this->identifier = identifier;
        this->password = password;
    }

    virtual ~GovernmentUser()
    {

    }
    

};
