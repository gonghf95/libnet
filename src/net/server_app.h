#ifndef NET_SERVERAPP_H
#define NET_SERVERAPP_H

#include "src/net/app_type.h"

#include <string>

template<typename App>
inline int MainTemplate()
{
    App* app = new App;
    app->InitApp();
    app->StartAllThread();
    app->Run();
    delete app;
    return 0;
}

class ThreadMgr;
class ServerApp
{
public:
    ServerApp(APP_TYPE type);
    virtual ~ServerApp();

    virtual void InitApp() = 0;

    void StartAllThread() const;
    void Run() const;
    void UpdateTime() const;

    bool AddListenerToThread(const std::string &ip, int port) const;

protected:
    ThreadMgr *threadMgr_;
    APP_TYPE type_;
};

#endif