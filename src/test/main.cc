#include "src/test/component.h"
#include "src/test/component_factory.h"
#include "src/test/component_register.h"
#include "src/test/concrete_component.h"
#include <iostream>

using namespace std;

template <typename... Args>
Component *CreateComponent(const std::string& classname, Args &&...args)
{
    return ComponentFactory<Args...>::GetInstance()->Create(classname, std::forward<Args>(args)...);
}

int main(int argc, char *argv[])
{
    ComponentRegister<ConcreteComponentA, std::string>();
    ComponentRegister<ConcreteComponentB, int>();

    CreateComponent(typeid(ConcreteComponentA).name(), std::string("aaa"));
    return 0;
}