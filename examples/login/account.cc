#include "account.h"
#include "src/net/protobuf/msg.pb.h"
#include "src/net/protobuf/proto_id.pb.h"
#include "src/net/packet.h"
#include "src/net/message_list.h"
#include "src/net/thread_mgr.h"
#include "http_request_account.h"
#include "player.h"

#include <iostream>

bool Account::Init()
{
    return true;
}

void Account::RegisterMsgFunc()
{
    ResgiterFunc(Proto::MsgId::C2L_AccountCheck, std::bind(&Account::HandleAccountCheck, this, std::placeholders::_1));
    ResgiterFunc(Proto::MsgId::MI_AccountCheckToHttpRs, std::bind(&Account::HandleAccountCheckToHttpRs, this, std::placeholders::_1));
}

void Account::Update()
{
}

void Account::HandleAccountCheck(Packet *pPacket)
{
    auto protoCheck = pPacket->ParseToProto<Proto::AccountCheck>();
    auto socket = pPacket->GetSocket();

    auto player = playerMgr_.GetPlayer(socket);
    if (nullptr != player)
    {
        Proto::AccountCheckRs protoResult;
        protoResult.set_return_code(Proto::AccountCheckRs::ARC_LOGGING);

        auto pPacketRs = new Packet(Proto::MsgId::C2L_AccountCheckRs, socket);
        pPacketRs->SerializeToBuffer(protoResult);
        SendPacket(pPacketRs);

        auto pPacketDis = new Packet(Proto::MsgId::MI_NetworkDisconnectToNet, socket);
        DispatchPacket(pPacketDis);

        return;
    }

    playerMgr_.AddPlayer(socket, protoCheck.account(), protoCheck.password());

    HttpRequestAccount *pHttp = new HttpRequestAccount(protoCheck.account(), protoCheck.password());
    ThreadMgr::GetInstance()->AddObjToThread(pHttp);
}

void Account::HandleAccountCheckToHttpRs(Packet *pPacket)
{
    auto proto = pPacket->ParseToProto<Proto::AccountCheckToHttpRs>();
    Player *pPlayer = playerMgr_.GetPlayer(proto.account());
    if (pPlayer == nullptr)
    {
        std::cout << "can't find player. account:" << proto.account().c_str() << std::endl;
        return;
    }

    std::cout << "account check result account:" << proto.account() << " rs:" << proto.return_code() << " socket:" << pPlayer->GetSocket() << std::endl;

    Proto::AccountCheckRs protoResult;
    protoResult.set_return_code(proto.return_code());

    auto pResultPacket = new Packet(Proto::MsgId::C2L_AccountCheckRs, pPlayer->GetSocket());
    pResultPacket->SerializeToBuffer(protoResult);
    SendPacket(pResultPacket);
}