#include "robot_state_login.h"
#include "robot.h"

void RobotStateLoginConnecting::OnEnterState()
{
}

RobotStateType RobotStateLoginConnecting::OnUpdate()
{
    if(pParentObj_->IsConnected())
    {
        return RobotState_Login_Connected;
    }
    return GetState();
}

void RobotStateLoginConnected::OnEnterState()
{
    pParentObj_->SendAccountCheckMsg();
}