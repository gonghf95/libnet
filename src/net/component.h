#ifndef NET_COMPONENT_H
#define NET_COMPONENT_H

class Entity;
class Component
{
public:
    Component();
    virtual ~Component();

    void setParent(Entity* parent) 
    { parent_ = parent; }
    Entity* parent() const 
    { return parent_; }
private:
    Entity* parent_;
};

#endif