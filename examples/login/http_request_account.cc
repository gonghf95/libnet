#include "http_request_account.h"
#include "src/net/packet.h"
#include "src/net/protobuf/proto_id.pb.h"
#include "src/net/protobuf/msg.pb.h"

#include <iostream>

HttpRequestAccount::HttpRequestAccount(std::string account, std::string password) :HttpRequest(account)
{
    _password = password;
    _curlRs = CRS_None;
    _method = HttpResquestMethod::HRM_Post;

    _url = "106.55.148.5:9004/member_login.php";
    _params.append("account=").append(_account).append("&password=").append(_password);

}

void HttpRequestAccount::ProcessMsg(Json::Value value)
{
    Proto::AccountCheckRs::ReturnCode code = Proto::AccountCheckRs::ARC_UNKONWN;
    int httpcode = value["returncode"].asInt();
    if (httpcode == 0)
        code = Proto::AccountCheckRs::ARC_OK;
    else if (httpcode == 2)
        code = Proto::AccountCheckRs::ARC_NOT_FOUND_ACCOUNT;
    else if (httpcode == 3)
        code = Proto::AccountCheckRs::ARC_PASSWORD_WRONG;

    std::cout << "code:" << code << std::endl;

    Proto::AccountCheckToHttpRs checkProto;
    checkProto.set_account(_account);
    checkProto.set_return_code(code);

    auto pCheckPacket = new Packet(Proto::MsgId::MI_AccountCheckToHttpRs, 0);
    pCheckPacket->SerializeToBuffer(checkProto);
    DispatchPacket(pCheckPacket);
}
