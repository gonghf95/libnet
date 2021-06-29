#ifndef NET_ENTITYSYSTEM_H
#define NET_ENTITYSYSTEM_H

#include "src/net/system.h"

#include <list>

class EntitySystem
{
public:
    virtual ~EntitySystem() = default;

    template <typename T, typename... TArgs>
    T *CreateComponent(TArgs &&...args);

    bool Update();

protected:
    std::list<IInitializeSystem *> initializeSystems_;
    std::list<IUpdateSystem *> updateSystems_;
};

template <typename T, typename... TArgs>
T *EntitySystem::CreateComponent(TArgs &&...args)
{
    auto component = new T(std::forward<TArgs>(args)...);

    // const auto objInit = dynamic_cast<IInitializeSystem *>(component);
    // if (objInit != nullptr)
    // {
    //     initializeSystems_.push_back(objInit);
    //     return component;
    // }

    const auto objUpdate = dynamic_cast<IUpdateSystem *>(component);
    if (objUpdate != nullptr)
    {
        updateSystems_.push_back(objUpdate);
        return component;
    }

    return component;
}

#endif