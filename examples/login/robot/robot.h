#ifndef ROBOT_H
#define ROBOT_H

#include "src/net/network_connector.h"
#include "robot_state_type.h"
#include "state_template.h"
#include "robot_state.h"

class Robot : public NetworkConnector, public StateTemplateMgr<RobotStateType, RobotState, Robot>
{
public:
    explicit Robot(const std::string &account);

    bool Init();
    void RegisterMsgFunc();
    void Update();

    void SendAccountCheckMsg();

    std::string GetAccount() const { return account_; }

protected:
    virtual void RegisterState();

    void HandleAccountCheckRs(Packet *);

private:
    std::string account_;
};

#endif