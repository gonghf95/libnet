#include "src/net/network_listen.h"
#include "src/net/connect_obj.h"

#include <errno.h>
#include <iostream>

bool NetworkListen::Init()
{
	return true;
}

bool NetworkListen::Listen(std::string ip, int port)
{
	masterSocket_ = CreateSocket();
	if(masterSocket_ == INVALID_SOCKET)
		return false;

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	::inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);

	SetSocketOpt(masterSocket_);

	if(::bind(masterSocket_, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		std::cout << "::bind(): " << strerror(errno) << std::endl;
		return false;
	}

	if(::listen(masterSocket_, SOMAXCONN) < 0)
	{
		std::cout << "::listen(): " << strerror(errno) << std::endl;
		return false;
	}

	return true;
}

void NetworkListen::Update()
{
	Select();
	if(FD_ISSET(masterSocket_, &readfds))
	{
		Accept();
	}

	Network::Update();
}

int NetworkListen::Accept()
{
	struct sockaddr addr;
	socklen_t len = sizeof(struct sockaddr);
	int rs = 0;
	while(true)
	{
		SOCKET socket = ::accept(masterSocket_, &addr, &len);
		if(socket == INVALID_SOCKET)
			break;

		SetSocketOpt(socket);

		ConnectObj* pConnectObj = new ConnectObj(this, socket);
		connects_.insert(std::make_pair(socket, pConnectObj));
		++rs;
	}
	return rs;
}
