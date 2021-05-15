#include "robot_app.h"
#include "src/net/app_type.h"
#include "src/net/thread_mgr.h"
#include "robot.h"

RobotApp::RobotApp()
    : ServerApp(APP_ROBOT)
{

}

void RobotApp::InitApp()
{
    Robot* robot = new Robot("test");
    // threadMgr_->AddThreadObj(robot);
    threadMgr_->AddObjToThread(robot);
}