#include "robot_state.h"
#include "robot.h"

RobotStateType RobotState::Update()
{
    const auto state = GetState();
    if(state > RobotState_Login_Connecting && state != RobotState_Login_Connecting)
    {
        if(!pParentObj_->IsConnected())
            return RobotState_Game_Connecting;
    }

    return OnUpdate();
}

void RobotState::EnterState()
{
    OnEnterState();
}

void RobotState::LeaveState()
{
    OnLeaveState();
}