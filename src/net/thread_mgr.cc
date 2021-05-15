#include "src/net/thread_mgr.h"
#include "src/net/thread_obj.h"
#include "src/net/thread.h"
#include "src/net/packet.h"
#include "src/net/network.h"
#include "src/net/network_listen.h"

#include <iostream>

ThreadMgr::~ThreadMgr()
{
    std::map<uint64_t, Thread *>::iterator it = threads_.begin();
    while (it != threads_.end())
    {
        delete it->second;
        it++;
    }
}

void ThreadMgr::StartAllThread()
{
    std::map<uint64_t, Thread *>::iterator it = threads_.begin();
    while (it != threads_.end())
    {
        it->second->Start();
        it++;
    }
}

bool ThreadMgr::IsLoop()
{
    std::map<uint64_t, Thread *>::iterator it = threads_.begin();
    while (it != threads_.end())
    {
        if (it->second->IsRun())
            return true;
        it++;
    }
    return false;
}

void ThreadMgr::NewThread()
{
    std::lock_guard<std::mutex> guard(mutex_);
    Thread *pThread = new Thread;
    threads_.insert(std::make_pair(pThread->GetSN(), pThread));
}

bool ThreadMgr::AddObjToThread(ThreadObj *obj)
{
    std::lock_guard<std::mutex> guard(mutex_);
    std::map<uint64_t, Thread *>::iterator it = threads_.begin();
    if (lastThreadSN_ > 0)
    {
        it = threads_.find(lastThreadSN_);
    }

    if (it == threads_.end())
    {
        std::cout << "AddThreadObj Failed. no thead." << std::endl;
        return false;
    }

    do
    {
        it++;
        if (it == threads_.end())
            it = threads_.begin();
    } while (!(it->second->IsRun()));

    Thread *pThread = it->second;
    pThread->AddThreadObj(obj);

    lastThreadSN_ = pThread->GetSN();

    return true;
}

void ThreadMgr::AddNetworkToThread(APP_TYPE type, Network *network)
{
    if (!AddObjToThread(network))
        return;

    std::lock_guard<std::mutex> guard(locatorLock_);
    networkLocator_[type] = network;
}

void ThreadMgr::DispatchPacket(Packet *packet)
{
    AddPacket(packet);

    std::lock_guard<std::mutex> guard(mutex_);
    for (auto it = threads_.begin(); it != threads_.end(); it++)
    {
        it->second->AddPacket(packet);
    }
}

void ThreadMgr::SendPacket(Packet *packet)
{
    NetworkListen *pLocator = static_cast<NetworkListen *>(GetNetwork(APP_LISTEN));
    pLocator->SendPacket(packet);
}

Network *ThreadMgr::GetNetwork(APP_TYPE type)
{
    auto it = networkLocator_.find(type);
    if (it == networkLocator_.end())
        return nullptr;
    return it->second;
}