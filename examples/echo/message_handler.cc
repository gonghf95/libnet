#include "message_handler.h"
#include "src/net/packet.h"
#include "src/net/protobuf/proto_id.pb.h"
#include "src/net/protobuf/msg.pb.h"

#include <functional>
#include <iostream>

bool MessageHandler::Init()
{
    return true;
}

void MessageHandler::RegisterMsgFunc()
{
    ResgiterFunc(Proto::MI_TestMsg, std::bind(&MessageHandler::HandleMsg, this, std::placeholders::_1));
}

void MessageHandler::Update()
{
}

void MessageHandler::HandleMsg(Packet *packet)
{
    auto obj = packet->ParseToProto<Proto::TestMsg>();
    std::cout << obj.msg().c_str() << std::endl;
}