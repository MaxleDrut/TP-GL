#include <assert.h>
#include <iostream>

#define NDEBUG

int main()
{
    std::cout << "test" << std::endl;

    assert(1 == 0);

    std::cout << "doit pas s'afficher" << std::endl;

    return 0;
}