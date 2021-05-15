#include "src/net/network_connector.h"
#include "src/net/connect_obj.h"

bool NetworkConnector::Init()
{
    return true;
}

void NetworkConnector::Update()
{
    if (INVALID_SOCKET == masterSocket_)
    {
        if (!Connect(ip_, port_))
            return;
    }

    Select();

    if (!IsConnected())
    {
        if (FD_ISSET(masterSocket_, &exceptfds))
        {
            return;
        }

        if (FD_ISSET(masterSocket_, &readfds) || FD_ISSET(masterSocket_, &writefds))
        {
            TryCreateConnectObj();
        }
    }

    Network::Update();
}

bool NetworkConnector::Connect(const std::string &ip, int port)
{
    ip_ = ip;
    port_ = port;

    if (ip.empty() || port <= 0)
        return false;

    masterSocket_ = CreateSocket();
    if (masterSocket_ <= 0)
        return false;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(port_);
    addr.sin_addr.s_addr = ::inet_addr(ip_.c_str());

    int rs = ::connect(masterSocket_, (struct sockaddr *)&addr, sizeof(addr));
    if (rs == 0)
    {
        CreateConnectObj(masterSocket_);
    }

    return true;
}

bool NetworkConnector::IsConnected() const
{
    return !connects_.empty();
}

void NetworkConnector::SendPacket(Packet *pPacket)
{
    ConnectObj *pConnect = GetConnectObj();
    if (pConnect == nullptr)
        return;

    pConnect->SendPacket(pPacket);
}

ConnectObj *NetworkConnector::GetConnectObj()
{
    std::map<SOCKET, ConnectObj *>::iterator it = connects_.find(masterSocket_);
    if (it == connects_.end())
        return nullptr;

    return it->second;
}

void NetworkConnector::TryCreateConnectObj()
{
    int optval = -1;
    socklen_t optlen = sizeof(optval);
    int rs = ::getsockopt(masterSocket_, SOL_SOCKET, SO_ERROR, (char *)(&optval), &optlen);
    if (rs == 0 && optval == 0)
    {
        CreateConnectObj(masterSocket_);
    }
}