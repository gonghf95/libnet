#ifndef ROBOTAPP_H
#define ROBOTAPP_H

#include "src/net/server_app.h"

class RobotApp : public ServerApp
{
public:
    RobotApp();
    void InitApp();
};

#endif