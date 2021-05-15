#include "login_app.h"
#include "src/net/app_type.h"
#include "src/net/thread_mgr.h"
#include "account.h"


LoginApp::LoginApp()
    : ServerApp(APP_LOGIN)
{
}

void LoginApp::InitApp()
{
    AddListenerToThread("0.0.0.0", 5188);

    Account* account = new Account();
    threadMgr_->AddObjToThread(account);
}