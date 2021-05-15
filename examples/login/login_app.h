#ifndef LOGINAPP_H
#define LOGINAPP_H

#include "src/net/server_app.h"

class LoginApp : public ServerApp
{
public:
    LoginApp();
    void InitApp();
};

#endif