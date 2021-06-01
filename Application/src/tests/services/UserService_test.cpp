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

int UserService_test::test_authentificate()
{
    string id = "Provider5";
    string pass = "provider0";

    User *  user = userServ->authentificate(id,pass);
    assert(user==nullptr);

    //TODO
    id = "Provider0";
    pass = "provider0";

    user = userServ->authentificate(id,pass);
    assert(user->getIdentifier()=="Provider0");
    assert(user->getPassword()=="provider0");

    

    cout<<"Test Authentification success"<<endl;

    return 0;
}

int UserService_test::test_getPrivilege(){
    UserTypes individual = userServ->getPrivilege("User0");
    UserTypes provider = userServ->getPrivilege("Provider0");
    UserTypes government = userServ->getPrivilege("Government0");
    UserTypes aucun = userServ->getPrivilege("harryPotter");

    assert(individual==INDIVIDUAL);
    assert(provider==PROVIDER);
    assert(government==GOVERNMENT);
    assert(aucun==NONE);

    cout<<"Valid privileges"<<endl;

    return 0;
    
    
}

int UserService_test::test_getIndividualUsers(){
    const vector<IndividualUser *> individuals= userServ->getIndividualUsers();
    
    assert(individuals[0]->getIdentifier()=="User0");
    assert(individuals[1]->getIdentifier()=="User1");

    cout<<"Valid individual users"<<endl;

    return 0;
    
}

int UserService_test::test_getProviderUsers(){
    const vector<ProviderUser *> providers= userServ->getProviderUsers();
    
    assert(providers[0]->getIdentifier()=="Provider0");
    assert(providers[1]->getIdentifier()=="Provider1");

    cout<<"Valid providers users"<<endl;

    return 0;
    
}