#pragma once

#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include "user/User.h"
#include "user/IndividualUser.h"
#include "user/ProviderUser.h"
#include "user/GovernmentUser.h"

using namespace std;


class UserService
{

    private :
        vector<User> users;

    public:

        UserService();

        virtual ~UserService();

        vector<User> getUsers () const;

        vector<IndividualUser> getIndividualUsers () const;

        vector<ProviderUser> getProviderUsers const;

        UserTypes getPrivilege(const string identifier) const;

        bool loadCSV (const string userFile, const string providerFile, const string governmentFile, const string passwordFile);

        User authentificate(const string login, const string pass);
        


};
