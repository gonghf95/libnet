#ifndef NET_TESTENTITY_H
#define NET_TESTENTITY_H

#include "src/net/entity.h"
#include "src/net/system.h"

class TestEntityWithUpdate : public Entity, public IUpdateSystem
{
public:
    virtual void Update() override;

private:
    bool isShow_{false};
};

class TestEntityWithInitialAndUpdate : public Entity, public IInitializeSystem, public IUpdateSystem
{
public:
    virtual void Initialize() override;
    virtual void Update() override;

private:
    bool isShow_{false};
};

#endif