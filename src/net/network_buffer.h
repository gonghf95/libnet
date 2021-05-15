#pragma once

#include "base_buffer.h"

#if TestNetwork
#define DEFAULT_SEND_BUFFER_SIZE	10
#define DEFAULT_RECV_BUFFER_SIZE	10
#else
#define DEFAULT_SEND_BUFFER_SIZE	1024 * 128
#define DEFAULT_RECV_BUFFER_SIZE	1024 * 128
#endif

class Packet;
class ConnectObj;

using TotalSizeType = unsigned short;

class NetworkBuffer : public Buffer
{
public:
	NetworkBuffer(const unsigned int size, ConnectObj* obj);

	virtual ~NetworkBuffer();

	bool HasData() const;

	unsigned int GetEmptySize() override;

	unsigned int GetWriteSize() const;

	unsigned int GetReadSize() const;

	void FillDate(unsigned int  size);
	void RemoveDate(unsigned int size);
	void ReAllocBuffer();

protected:
	unsigned int _dataSize;
	ConnectObj* obj_;
};


class RecvNetworkBuffer : public NetworkBuffer {
public:
	RecvNetworkBuffer(unsigned int _size, ConnectObj* obj);
	void Dispose() override;
	int GetBuffer(char*& pBuffer) const;
	Packet* GetPacket();

private:
	void MemcpyFromBuffer(char* pVoid, unsigned int size);
};

class SendNetworkBuffer : public NetworkBuffer {
public:
	SendNetworkBuffer(unsigned int _size, ConnectObj* obj);
	void Dispose() override;
	int GetBuffer(char*& pBuffer) const;
	void AddPacket(Packet* pPacket);

private:
	void MemcpyToBuffer(char* pVoid, unsigned int size);
};
