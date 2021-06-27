#ifndef NET_ENTITY_H
#define NET_ENTITY_H

#include "src/net/component.h"

#include <vector>
#include <algorithm>

class Entity : public Component
{
public:
    void addComponent(Component *component);

    template <typename T>
    T *getComponent();

private:
    std::vector<Component *> components_;
};

template <typename T>
T *Entity::getComponent()
{
    auto it = std::find_if(components_.begin(), components_.end(), [](Component *component)
                           { return dynamic_cast<T>(component) != nullptr; });

    if (it == components_.end())
        return false;
    
    return dynamic_cast<T>(*it);
}

#endif