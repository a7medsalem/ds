#include <iostream>

#include "global.h"
#include "ArrayList.h"

int main()
{
    ds::ArrayList<INT> list;
    ds::ArrayList<INT> copy = list;

    std::cout << "List size is " << list.getSize() << std::endl;
    std::cout << "Copy size is " << copy.getSize() << std::endl;
    return 0;
}