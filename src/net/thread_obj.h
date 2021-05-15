#ifndef NET_THREADOBJ_H
#define NET_THREADOBJ_H

#include "src/net/message_list.h"

class ThreadObj : public MessageList
{
public:
	ThreadObj();
	virtual ~ThreadObj() {}

	virtual bool Init() = 0;
	virtual void RegisterMsgFunc() = 0;
	virtual void Update() = 0;

	bool IsActive() const;

protected:
	bool active_;
};

#endif
