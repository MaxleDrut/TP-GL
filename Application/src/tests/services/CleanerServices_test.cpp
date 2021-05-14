#include "CleanerServices_test.h"

CleanerServices_test::CleanerServices_test(){
    cleaner = new CleanerService();
}

CleanerServices_test::~CleanerServices_test(){
    delete cleaner;
}
