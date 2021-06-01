#pragma once
 
#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

#include "services/UserService.h"
#include "user/User.h"
#include "services/LoadService.h"

class UserService_test
{
    private:
        UserService * userServ;

    public:
        UserService_test();
        virtual ~UserService_test();
        int test_authentificate();
        int test_getPrivilege();
        int test_getIndividualUsers();
        int test_getProviderUsers();
};