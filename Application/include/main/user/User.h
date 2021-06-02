#pragma once

#include <string>
#include <iostream>

using namespace std;

enum UserTypes {
    INDIVIDUAL,
    PROVIDER,
    GOVERNMENT,
    NONE
};

string UserTypeToString(UserTypes &userType);


class User
{
private:
    string identifier;
    string password;
    
public:
    User() = default;

    User(string &identifier, string &password): identifier(identifier), password(password) {};

    virtual ~User() = default;

    virtual string getIdentifier() const
    {
        return identifier;
    }

    virtual string getPassword() const
    {
        return password;
    }
};

