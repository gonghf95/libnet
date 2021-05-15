#include "src/net/thread_obj.h"

ThreadObj::ThreadObj()
	: active_(true)
{
}

bool ThreadObj::IsActive() const
{
	return active_;
}
