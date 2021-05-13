#include "CleanerServices_test.h"

CleanerServices_test::CleanerServices_test(){
    cleaner = new CleanerService();
}

CleanerServices_test::~CleanerServices_test(){
    delete cleaner;
}

void CleanerServices_test::test_loadCSV(string & file){
    
    bool res = cleaner->loadCSV(file);
    assert(res==true);
    assert(cleaner->getCleaners().size()==2);
    cout << "Le test est réussi" <<endl;

}