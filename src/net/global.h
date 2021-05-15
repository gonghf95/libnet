#ifndef NET_GLOBAL_H
#define NET_GLOBAL_H

#include "src/net/singleton.h"
#include <stdint.h>
#include <mutex>

class Global : public Singleton<Global>
{
public:
    uint64_t GenerateSN();

private:
    uint64_t sn_ {0};
    std::mutex mutex_;
};

#endif