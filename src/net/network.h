#ifndef NET_NETWORK_H
#define NET_NETWORK_H

#include "src/net/disposable.h"
#include "src/net/thread_obj.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <iostream>

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SOCKET int
#define INVALID_SOCKET -1

class ConnectObj;
class Network : public IDisposable, public ThreadObj
{
public:
	Network();

	void Dispose();
	bool Select();
	void Update() override;
	void RegisterMsgFunc() override;
	void SendPacket(Packet*);

	SOCKET GetSocket() const { return masterSocket_; }
	
protected:
	static void SetSocketOpt(SOCKET socket);
	SOCKET CreateSocket();
	void CreateConnectObj(SOCKET socket);

protected:
	SOCKET masterSocket_;
	std::map<SOCKET, ConnectObj*> connects_;
	fd_set readfds, writefds, exceptfds;

	std::mutex sendMsgMutex_;
	std::list<Packet*> sendMsgList_;
};

#endif /* NET_NETWORK_H */
