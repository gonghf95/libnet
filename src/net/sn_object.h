#ifndef NET_SNOBJECT_H
#define NET_SNOBJECT_H

#include "src/net/global.h"
#include <stdint.h>

class SnObject
{
public:
    SnObject()
    {
        sn_ = Singleton<Global>::GetInstance()->GenerateSN();
    }

    SnObject(uint64_t sn) : sn_(sn)
    {
    }

    virtual ~SnObject() {}

    uint64_t GetSN() const
    {
        return sn_;
    }

protected:
    uint64_t sn_;
};

#endif