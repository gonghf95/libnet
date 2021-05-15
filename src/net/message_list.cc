#include "src/net/message_list.h"
#include "src/net/packet.h"
#include "src/net/thread_mgr.h"

void MessageList::ResgiterFunc(int msgid, MessageFunc func)
{
    std::lock_guard<std::mutex> guard(mutex_);
    callbacks_[msgid] = func;
}

bool MessageList::IsFollowMsgId(int msgid)
{
    std::lock_guard<std::mutex> guard(mutex_);
    return callbacks_.find(msgid) != callbacks_.end();
}

void MessageList::ProcessPacket()
{
    std::list<Packet *> tmplist;

    {
        std::lock_guard<std::mutex> guard(mutex_);
        std::copy(msglist_.begin(), msglist_.end(), std::back_inserter(tmplist));
        msglist_.clear();
    }

    for (auto packet : tmplist)
    {
        auto it = callbacks_.find(packet->GetMsgId());
        if (it != callbacks_.end() && it->second)
        {
            it->second(packet);
        }
    }
}

void MessageList::AddPacket(Packet *packet)
{
    std::lock_guard<std::mutex> guard(mutex_);
    msglist_.push_back(packet);
}

void MessageList::DispatchPacket(Packet *pPacket)
{
    ThreadMgr::GetInstance()->DispatchPacket(pPacket);
}

void MessageList::SendPacket(Packet *pPacket)
{
    ThreadMgr::GetInstance()->SendPacket(pPacket);
}