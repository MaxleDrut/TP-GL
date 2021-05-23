//
// Created by onyr on 07/05/2021.
//


#include "UserService_test.h"


using namespace std;

UserService_test::UserService_test(){
    LoadService loadService;
    string fileUsers= "res/test/users.csv";
    string fileProviders= "res/test/providers.csv";
    string fileGovernment= "res/test/government.csv";
    string filePassword= "res/test/password.csv";
    bool res = loadService.loadUsers(fileUsers,fileProviders,fileGovernment,filePassword);
    vector<User *> users = loadService.getUsers();
    userServ = new UserService(users);
}

UserService_test::~UserService_test(){
    delete userServ;
}

int UserService_test::test_authentificate(const string login, const string pass)
{
    //TODO
    User * user = userServ->authentificate(login,pass);
    assert(user->getIdentifier()=="Provider0");
    assert(user->getPassword()=="provider0");

    cout<<"Authentification success"<<endl;

    return 0;
}