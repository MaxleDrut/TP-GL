#include <assert.h>
#include <iostream>

#include "CleanerServices_test.h"

#define NDEBUG

void tests_CleanersLoadCSV();

int main()
{
    tests_CleanersLoadCSV();
    return 0;
}


void tests_CleanersLoadCSV(){
    CleanerServices_test * testsCleaners = new  CleanerServices_test();

    //Test avec la bonne file
    string file1 = "res/test/cleaners.csv";
    testsCleaners->test_loadCSV(file1);

    /*Test avec une mauvaise file
    string file2 = "aaaa.csv";
    testsCleaners->test_loadCSV(file2);*/

    delete(testsCleaners);
}