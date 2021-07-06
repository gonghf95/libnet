#ifndef COMPONENTREGISTER_H
#define COMPONENTREGISTER_H

#include "src/test/component_factory.h"

template <typename T, typename... Args>
class ComponentRegister
{
public:
    ComponentRegister()
    {
        std::string classname = typeid(T).name();
        ComponentFactory<Args...>::GetInstance()->Regist(classname, CreateComponent);
    }

    static Component *CreateComponent(Args &&...args)
    {
        return new T(std::forward<Args>(args)...);
    }
};

#endif