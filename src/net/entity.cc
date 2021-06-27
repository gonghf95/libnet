#include "src/net/entity.h"
#include "src/net/component.h"

void Entity::addComponent(Component* component)
{
    component->setParent(this);
    components_.push_back(component);
}