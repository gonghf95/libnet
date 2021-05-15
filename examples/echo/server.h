#ifndef NET_SERVER_H
#define NET_SERVER_H

#include "src/net/server_app.h"

class Server : public ServerApp
{
public:
	virtual void InitApp();
};

#endif
