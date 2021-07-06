#ifndef CONCRETECOMPONENT_H
#define CONCRETECOMPONENT_H

#include "src/test/component.h"
#include <string>
#include <iostream>

class ConcreteComponentA : public Component
{
public:
    ConcreteComponentA(const std::string &)
    {
        std::cout << __func__ << std::endl;
    }
};

class ConcreteComponentB : public Component
{
public:
    ConcreteComponentB(int a)
    {
        std::cout << __func__ << std::endl;
    }
};

#endif