#ifndef NET_NETWORK_LISTEN_H
#define NET_NETWORK_LISTEN_H

#include "src/net/network.h"
#include <string>

class NetworkListen : public Network
{
public:

	bool Init() override;
	bool Listen(std::string ip, int port);
	void Update() override;
	
protected:
	virtual int Accept();
};

#endif /* NET_NETWORK_LISTEN_H */
