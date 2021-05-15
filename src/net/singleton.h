#ifndef NET_SINGLETON_H
#define NET_SINGLETON_H

#include <stdexcept>

template <typename T>
class Singleton
{
public:
    static T* Instance()
    {
        if (nullptr == instance_)
        {
            instance_ = new T;
        }
        return instance_;
    }

    static T *GetInstance()
    {
        if (instance_ == nullptr)
            throw std::logic_error("the instance is't init, please initialisze the instance first");
        return instance_;
    }

    static void DestroyInstance()
    {
        delete instance_;
        instance_ = nullptr;
    }

protected:
    Singleton() {}
    Singleton(const Singleton &) {}
    void operator=(const Singleton &) {}

private:
    static T *instance_;
};

template <typename T>
T *Singleton<T>::instance_ = nullptr;

#endif