#ifndef NET_THREADMGR_H
#define NET_THREADMGR_H

#include "src/net/singleton.h"
#include "src/net/app_type.h"
#include "src/net/thread.h"

#include <mutex>
#include <map>
#include <stdint.h>

class Thread;
class ThreadObj;
class Packet;
class Network;
class ThreadMgr : public Singleton<ThreadMgr>, public ThreadObjList
{
public:
    ~ThreadMgr();

    void StartAllThread();
    bool IsLoop();
    void NewThread();
    bool AddObjToThread(ThreadObj *obj);
    void AddNetworkToThread(APP_TYPE type, Network *);

    void DispatchPacket(Packet *);
    void SendPacket(Packet *);

private:
    Network* GetNetwork(APP_TYPE);

private:
    std::mutex mutex_;
    std::map<uint64_t, Thread *> threads_;

    uint64_t lastThreadSN_{0};

    std::mutex locatorLock_;
    std::map<APP_TYPE, Network *> networkLocator_;
};

#endif