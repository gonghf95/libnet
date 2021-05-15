#ifndef NET_MESSAGELIST_H
#define NET_MESSAGELIST_H

#include <mutex>
#include <functional>
#include <map>
#include <list>

class Packet;
class MessageList
{
public:
    typedef std::function<void(Packet *)> MessageFunc;
    void ResgiterFunc(int msgid, MessageFunc func);
    bool IsFollowMsgId(int);
    void ProcessPacket();
    void AddPacket(Packet *);

    static void DispatchPacket(Packet *);
    static void SendPacket(Packet *);

protected:
    std::mutex mutex_;
    std::list<Packet *> msglist_;
    std::map<int, MessageFunc> callbacks_;
};

#endif