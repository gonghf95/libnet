#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include "state_template.h"
#include "robot_state_type.h"

class Robot;
class RobotState : public StateTemplate<RobotStateType, Robot>
{
public:
    RobotStateType Update();
    virtual RobotStateType OnUpdate()
    {
        return GetState();
    }

    void EnterState();
    virtual void OnEnterState() {}

    void LeaveState();
    virtual void OnLeaveState() {}
};

#endif