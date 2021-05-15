#include "src/net/network.h"
#include "src/net/connect_obj.h"
#include "src/net/packet.h"
#include <iostream>

Network::Network()
	: masterSocket_(-1)
{
}

void Network::Dispose()
{

}

bool Network::Select()
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);

	FD_SET(masterSocket_, &readfds);
	FD_SET(masterSocket_, &writefds);
	FD_SET(masterSocket_, &exceptfds);
	
	SOCKET maxfd = masterSocket_;
	for(auto it=connects_.begin(); it!=connects_.end(); ++it)
	{
		if(maxfd < it->first)
			maxfd = it->first;

		FD_SET(it->first, &readfds);
		FD_SET(it->first, &exceptfds);
		if(it->second->HasSendData())
		{
			FD_SET(it->first, &writefds);
		}
		else
		{
			if(it->first == masterSocket_)
			{
				FD_CLR(masterSocket_, &writefds);
			}
		}
	}

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 50 * 1000;

	int nfds = ::select(maxfd+1, &readfds, &writefds, &exceptfds, &timeout);
	if(nfds <= 0)
		return true;

	auto it = connects_.begin();
	while(it!=connects_.end())
	{
		if(FD_ISSET(it->first, &exceptfds))
		{
			it->second->Dispose();
			delete it->second;
			it = connects_.erase(it);
			continue;
		}

		if(FD_ISSET(it->first, &readfds))
		{
			if(!it->second->Recv())
			{
				continue;
			}
		}

		if(FD_ISSET(it->first, &writefds))
		{
			if(!it->second->Send())
			{
				continue;
			}
		}

		++it;
	}

	return true;
}

void Network::Update()
{
    std::list<Packet*> tmpSendMsgList;
    sendMsgMutex_.lock();
    std::copy(sendMsgList_.begin(), sendMsgList_.end(), std::back_inserter(tmpSendMsgList));
    sendMsgList_.clear();
    sendMsgMutex_.unlock();

    for (auto pPacket : tmpSendMsgList)
    {
        auto iter = connects_.find(pPacket->GetSocket());
        if (iter == connects_.end())
        {
            std::cout << "UpdateSendPacket. can't find socket." << std::endl;
            continue;
        }

        iter->second->SendPacket(pPacket);
    }

    tmpSendMsgList.clear();
}

void Network::RegisterMsgFunc()
{
	
}

void Network::SendPacket(Packet* packet)
{
	std::lock_guard<std::mutex> guard(sendMsgMutex_);
    sendMsgList_.push_back(packet);
}

void Network::SetSocketOpt(SOCKET socket)
{
	bool isReuseAddr = true;
	setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (void*)&isReuseAddr, sizeof(isReuseAddr));

	int timeout = 3000;
	setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
	setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	int flags = fcntl(socket, F_GETFL, 0);
	fcntl(socket, F_SETFL, flags|O_NONBLOCK);
}

SOCKET Network::CreateSocket()
{
	SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == socket)
	{
		std::cout << "::socket failed.\n";
		return -1;
	}

	SetSocketOpt(socket);

	return socket;
}

void Network::CreateConnectObj(SOCKET socket)
{
	ConnectObj* pConnectObj = new ConnectObj(this, socket);
	connects_.insert(std::make_pair(socket, pConnectObj));
}