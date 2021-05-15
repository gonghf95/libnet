#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "src/net/sn_object.h"

#include <list>
#include <thread>
#include <mutex>

class ThreadObj;
class Packet;

class ThreadObjList
{
public:
	void Update();
	void AddThreadObj(ThreadObj *obj);
	void AddPacket(Packet *pPacket);

protected:
	std::list<ThreadObj *> objlist_;
	std::mutex mutex_;
};

class Thread : public SnObject, public ThreadObjList
{
public:
	Thread();
	virtual ~Thread();

	void Start();
	void Stop();

	bool IsRun() const { return isRun_; }

private:
	bool isRun_;
	std::thread thread_;
};

#endif
