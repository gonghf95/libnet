#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "src/net/thread_obj.h"

class Packet;
class MessageHandler : public ThreadObj
{
public:
    virtual bool Init();
    virtual void RegisterMsgFunc();
    virtual void Update();

private:
    void HandleMsg(Packet*);
};

#endif