#include "robot.h"
#include "src/net/protobuf/msg.pb.h"
#include "src/net/protobuf/proto_id.pb.h"
#include "src/net/packet.h"
#include "robot_state_login.h"

#include <functional>

Robot::Robot(const std::string& account)
    : account_(account)
{

}

bool Robot::Init()
{
    InitStateTemplateMgr(RobotStateType::RobotState_Login_Connecting);
    Connect("127.0.0.1", 5188);
    return true;
}

void Robot::RegisterMsgFunc()
{
    ResgiterFunc(Proto::MsgId::C2L_AccountCheckRs, std::bind(&Robot::HandleAccountCheckRs, this, std::placeholders::_1));
}

void Robot::Update()
{
    NetworkConnector::Update();
    UpdateState();
}

void Robot::SendAccountCheckMsg()
{
    Proto::AccountCheck protoAccountCheck;
    protoAccountCheck.set_account(GetAccount());
    protoAccountCheck.set_password("e10adc3949ba59abbe56e057f20f883e");

    auto packet = new Packet(Proto::MsgId::C2L_AccountCheck, GetSocket());
    packet->SerializeToBuffer(protoAccountCheck);
    SendPacket(packet);
}

void Robot::RegisterState()
{
    RegisterStateClass(RobotStateType::RobotState_Login_Connecting, DynamicStateBind(RobotStateLoginConnecting));
    RegisterStateClass(RobotStateType::RobotState_Login_Connected, DynamicStateBind(RobotStateLoginConnected));
    RegisterStateClass(RobotStateType::RobotState_Login_Logined, DynamicStateBind(RobotStateLoginLogined));
}

void Robot::HandleAccountCheckRs(Packet * packet)
{
    Proto::AccountCheckRs proto = packet->ParseToProto<Proto::AccountCheckRs>();
    std::cout << "account check result account:" << GetAccount() << " code:" << proto.return_code() << std::endl;

    if (proto.return_code() == Proto::AccountCheckRs::ARC_OK)
        ChangeState(RobotStateType::RobotState_Login_Logined);
}