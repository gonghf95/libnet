#include "robot.h"
#include "src/net/packet.h"
#include "src/net/connect_obj.h"
#include "src/net/protobuf/msg.pb.h"
#include "src/net/protobuf/proto_id.pb.h"

bool Robot::Init()
{
    Connect("127.0.0.1", 5188);
    return true;
}

void Robot::Update()
{
    NetworkConnector::Update();

    if(IsConnected() && !isSendMsg_)
    {
        // Proto::TestMsg msg;
        // msg.set_msg("test msg");

        // Packet* packet = new Packet((int)Proto::MI_TestMsg, masterSocket_);
        // packet->SerializeToBuffer<Proto::TestMsg>(msg);
        // SendPacket(packet);
        isSendMsg_ = true;
    }
}