#include "src/net/test_entity.h"
#include <iostream>
#include <typeinfo>

void TestEntityWithUpdate::Update()
{
    if (isShow_)
        return;

    std::cout << typeid(this).name() << "::Update" << std::endl;
    isShow_ = true;
}

void TestEntityWithInitialAndUpdate::Initialize()
{
    std::cout << typeid(this).name() << "::Initialize" << std::endl;
}

void TestEntityWithInitialAndUpdate::Update()
{
    if (isShow_)
        return;

    std::cout << typeid(this).name() << "::Update" << std::endl;
    isShow_ = true;
}