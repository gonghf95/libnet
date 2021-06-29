#ifndef NET_TESTCUPDATE_H
#define NET_TESTCUPDATE_H

#include "src/net/system.h"
#include "src/net/component.h"

class TestCUpdate : public Component, public IUpdateSystem
{
public:
    virtual void Update() override;

private:
    bool isShow_{false};
};

#endif