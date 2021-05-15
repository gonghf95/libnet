#include "server.h"
#include "src/net/connect_obj.h"
#include "src/net/packet.h"
#include "src/net/thread_mgr.h"
#include "message_handler.h"

void Server::InitApp()
{
	AddListenerToThread("127.0.0.1", 5188);
	threadMgr_->AddObjToThread(new MessageHandler);
}
