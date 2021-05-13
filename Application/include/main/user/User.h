#pragma once

#include <string>

using namespace std;

enum UserTypes {
    INDIVIDUAL,
    PROVIDER,
    GOVERNMENT,
    AUCUN
};

class User
{
protected:
    string identifier;
    string password;
    
public:
    User() = default;

    string getIdentifier()
    {
        return this->identifier;
    }

    string getPassword()
    {
        return this->password;
    }
};
