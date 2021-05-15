#ifndef NET_CONNECTOBJ_H
#define NET_CONNECTOBJ_H

#include "src/net/disposable.h"
#include "src/net/network.h"
#include "src/net/message_list.h"

class RecvNetworkBuffer;
class SendNetworkBuffer;
class Packet;

class ConnectObj : public IDisposable, public MessageList
{
public:
    ConnectObj(Network *pNetWork, SOCKET socket);
    ~ConnectObj() override;

    void Dispose() override;

    SOCKET GetSocket() const { return _socket; }
    bool HasRecvData() const;
    Packet *GetRecvPacket() const;
    bool Recv() const;

    bool HasSendData() const;
    void SendPacket(Packet *pPacket) const;
    bool Send() const;

protected:
    Network *_pNetWork{nullptr};
    const SOCKET _socket;
    RecvNetworkBuffer *_recvBuffer{nullptr};
    SendNetworkBuffer *_sendBuffer{nullptr};
};

#endif