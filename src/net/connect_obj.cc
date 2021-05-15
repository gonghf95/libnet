#include "src/net/connect_obj.h"
#include "src/net/network.h"
#include "src/net/network_buffer.h"
#include "src/net/packet.h"
#include "src/net/thread_mgr.h"

#include <iostream>

ConnectObj::ConnectObj(Network *pNetWork, SOCKET socket) : _pNetWork(pNetWork), _socket(socket)
{
	_recvBuffer = new RecvNetworkBuffer(DEFAULT_RECV_BUFFER_SIZE, this);
	_sendBuffer = new SendNetworkBuffer(DEFAULT_SEND_BUFFER_SIZE, this);
}

ConnectObj::~ConnectObj()
{
	if (_recvBuffer != nullptr)
		delete _recvBuffer;

	if (_sendBuffer != nullptr)
		delete _sendBuffer;
}

void ConnectObj::Dispose()
{
	::close(_socket);

	_recvBuffer->Dispose();
	_sendBuffer->Dispose();
}

bool ConnectObj::HasRecvData() const
{
	return _recvBuffer->HasData();
}

Packet *ConnectObj::GetRecvPacket() const
{
	return _recvBuffer->GetPacket();
}

bool ConnectObj::Recv() const
{
	char *pBuffer = nullptr;
	bool isRs = false;
	while (true)
	{
		if (_recvBuffer->GetEmptySize() < (sizeof(PacketHead) + sizeof(TotalSizeType)))
		{
			_recvBuffer->ReAllocBuffer();
		}

		const int emptySize = _recvBuffer->GetBuffer(pBuffer);
		const int dataSize = ::recv(_socket, pBuffer, emptySize, 0);
		if (dataSize > 0)
		{
			_recvBuffer->FillDate(dataSize);
		}
		else if (dataSize == 0)
		{
			isRs = false;
			break;
		}
		else
		{
			if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
			{
				isRs = true;
				break;
			}

			isRs = false;
			break;
		}
	}

	if (isRs)
	{

		while (true)
		{
			Packet *packet = _recvBuffer->GetPacket();
			if (packet == nullptr)
				break;
			ThreadMgr::GetInstance()->DispatchPacket(packet);
		}
	}

	return isRs;
}

bool ConnectObj::HasSendData() const
{
	return _sendBuffer->HasData();
}

void ConnectObj::SendPacket(Packet *pPacket) const
{
	_sendBuffer->AddPacket(pPacket);
}

bool ConnectObj::Send() const
{
	while (true)
	{
		char *pBuffer = nullptr;
		const int needSendSize = _sendBuffer->GetBuffer(pBuffer);

		if (needSendSize <= 0)
		{
			return true;
		}

		const int size = ::send(_socket, pBuffer, needSendSize, 0);
		if (size > 0)
		{
			_sendBuffer->RemoveDate(size);

			if (size < needSendSize)
			{
				return true;
			}
		}

		if (size == -1)
		{
			std::cout << "needSendSize:" << needSendSize << " error:" << errno << std::endl;
			return false;
		}
	}
}
