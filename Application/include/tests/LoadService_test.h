
#pragma once
 
#include <assert.h>
#include <typeinfo>
#include <iostream>

using namespace std;

#include "services/LoadService.h"

class LoadService_test
{
    private:
        LoadService * load;

    public:
        LoadService_test();
        virtual ~LoadService_test();
        int test_loadCleaners(string &file);
        int test_loadSensors(string & file1, string & file2, string & file3);
        int test_loadUsers(string & userFile, string & providerFile, string & governmentFile, string & passwordFile);
};     
        