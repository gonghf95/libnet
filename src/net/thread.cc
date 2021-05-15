#include "src/net/thread.h"
#include "src/net/thread_obj.h"
#include "src/net/packet.h"

#include <iostream>

void ThreadObjList::Update()
{
	std::list<ThreadObj*> tmpObjs;

	mutex_.lock();
	std::copy(objlist_.begin(), objlist_.end(), std::back_inserter(tmpObjs));
	mutex_.unlock();

	for (ThreadObj *pObj : tmpObjs)
	{
		pObj->ProcessPacket();
		pObj->Update();

		if (!pObj->IsActive())
		{
			mutex_.lock();
			objlist_.remove(pObj);
			mutex_.unlock();

			delete pObj;
		}
	}

	tmpObjs.clear();
}

void ThreadObjList::AddThreadObj(ThreadObj *obj)
{
	std::lock_guard<std::mutex> guard(mutex_);

	if(!obj->Init())
	{
		std::cout << "AddObject Failed. ThreadObject init failed.\n";
		return ;
	}

	obj->RegisterMsgFunc();
	objlist_.push_back(obj);
}

void ThreadObjList::AddPacket(Packet *packet)
{
	std::lock_guard<std::mutex> guard(mutex_);
	for (auto it = objlist_.begin(); it != objlist_.end(); it++)
	{
		ThreadObj *obj = *it;
		if (obj->IsFollowMsgId(packet->GetMsgId()))
		{
			obj->AddPacket(packet);
		}
	}
}

Thread::Thread()
	: isRun_(true)
{
}

Thread::~Thread()
{
	std::list<ThreadObj *>::iterator it = objlist_.begin();
	while (it != objlist_.end())
	{
		delete *it;
		it = objlist_.erase(it);
	}
	objlist_.clear();
}

void Thread::Start()
{
	isRun_ = true;
	thread_ = std::thread([this]()
						  {
							  while (isRun_)
							  {
								  Update();
							  }
						  });
}

void Thread::Stop()
{
	if (isRun_)
	{
		isRun_ = false;
		if (thread_.joinable())
			thread_.join();
	}
}