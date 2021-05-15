#ifndef ROBOT_H
#define ROBOT_H

#include "src/net/network_connector.h"

class Robot : public NetworkConnector
{
public:
    virtual bool Init();
    virtual void Update();

private:
    bool isSendMsg_{false};
};

#endif