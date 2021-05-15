#include "robot_app.h"
#include "robot.h"
#include "src/net/thread_mgr.h"

RobotApp::RobotApp()
    : ServerApp(APP_ROBOT)
{
}

void RobotApp::InitApp()
{
    for (int i = 0; i < 10; i++)
    {
        Robot *robot = new Robot;
        threadMgr_->AddObjToThread(robot);
    }
}