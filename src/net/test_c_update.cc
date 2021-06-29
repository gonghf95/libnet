#include "src/net/test_c_update.h"

#include <typeinfo>
#include <iostream>

void TestCUpdate::Update()
{
    if (isShow_)
        return;

    std::cout << typeid(this).name() << "::Update" << std::endl;
    isShow_ = true;
}