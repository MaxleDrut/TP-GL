#pragma once

#include <string>
#include <vector>

#include "User.h"

using namespace std;


class IndividualUser: User
{

private:

    
public:

    IndividualUser(string identifier, string password)
    {
        this->identifier = identifier;
        this->password = password;
    }

    virtual ~IndividualUser()
    {
        
    }

};
