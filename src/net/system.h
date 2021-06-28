#ifndef NET_SYSTEM_H
#define NET_SYSTEM_H

class ISystem
{
public:
    virtual ~ISystem() = default;

protected:
    ISystem() = default;
};

class IInitializeSystem : virtual public ISystem
{
public:
    virtual ~IInitializeSystem() = default;

    virtual void Initialize() = 0;

protected:
    IInitializeSystem() = default;
};

class IUpdateSystem : virtual public ISystem
{
public:
    virtual ~IUpdateSystem() = default;

    virtual void Update() = 0;

protected:
    IUpdateSystem() = default;
};

#endif