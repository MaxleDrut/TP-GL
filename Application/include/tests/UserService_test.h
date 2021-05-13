#pragma once
 
#include <assert.h>
#include <iostream>
using namespace std;

#include "services/UserService.h"

class UserService_test
{
    private:
        UserService * user;

    public:
        UserService_test();
        virtual ~UserService_test();
        void test_authentificate(const string login, const string pass);
};