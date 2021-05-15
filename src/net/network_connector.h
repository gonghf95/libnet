#ifndef NET_NETWORKCONNECTOR_H
#define NET_NETWORKCONNECTOR_H

#include "src/net/network.h"

class NetworkConnector : public Network
{
public:
    bool Init() override;
    void Update() override;

    bool Connect(const std::string &ip, int port);
    bool IsConnected() const;

    void SendPacket(Packet *pPacket);

protected:
    std::string ip_;
    int port_;

private:
    ConnectObj *GetConnectObj();
    void TryCreateConnectObj();
};

#endif