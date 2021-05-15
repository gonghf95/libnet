#include "src/net/server_app.h"
#include "src/net/thread_mgr.h"
#include "src/net/network_listen.h"
#include "src/net/global.h"

#include <iostream>

using std::cout;
using std::endl;

ServerApp::ServerApp(APP_TYPE type)
    : type_(type)
{
    Global::Instance();
    threadMgr_ = ThreadMgr::Instance();
    for(int i=0; i<3; i++)
    {
        threadMgr_->NewThread();
    }
}

ServerApp::~ServerApp()
{

}

void ServerApp::StartAllThread() const
{
    threadMgr_->StartAllThread();
}

void ServerApp::Run() const
{
    bool isRun = true;
    while(isRun)
    {
        threadMgr_->Update();
        isRun = threadMgr_->IsLoop();
    }
}

bool ServerApp::AddListenerToThread(const std::string& ip, int port) const
{
    NetworkListen* pNetworkListen = new NetworkListen;
    if(!pNetworkListen->Listen(ip, port))
    {
        delete pNetworkListen;
        return false;
    }
    threadMgr_->AddNetworkToThread(APP_LISTEN, pNetworkListen);
    return true;
}