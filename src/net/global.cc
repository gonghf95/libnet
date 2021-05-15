#include "src/net/global.h"

uint64_t Global::GenerateSN()
{
    std::lock_guard<std::mutex> guard(mutex_);
    sn_ += 1;
    return sn_;
}