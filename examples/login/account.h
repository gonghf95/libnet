#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "src/net/thread_obj.h"
#include "player_mgr.h"

class Account : public ThreadObj
{
public:
    virtual bool Init();
    virtual void RegisterMsgFunc();
    virtual void Update();

private:
    void HandleAccountCheck(Packet *pPacket);
    void HandleAccountCheckToHttpRs(Packet *pPacket);

private:
    PlayerMgr playerMgr_;
};

#endif