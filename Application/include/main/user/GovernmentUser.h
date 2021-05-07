#pragma once

#include <string>
#include "user/User.h"

using namespace std;


class GovernmentUser : User
{
public:
    GovernmentUser(const string &identifier, const string &password)
    {
        this->identifier = identifier;
        this->password = password;
    }

    virtual ~GovernmentUser() = default;
};
