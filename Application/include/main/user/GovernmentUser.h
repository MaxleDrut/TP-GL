#pragma once

#include <string>
#include "user/User.h"

using namespace std;


class GovernmentUser : public User
{
public:
    GovernmentUser(string &identifier, string &password): User(identifier, password) {};

    virtual ~GovernmentUser() = default;
};
