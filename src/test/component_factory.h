#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "src/test/component.h"

#include <string>
#include <functional>
#include <unordered_map>

template <typename... Args>
class ComponentFactory
{
public:
    static ComponentFactory *GetInstance()
    {
        if (instance_ == nullptr)
            instance_ = new ComponentFactory;
        return instance_;
    }

    bool Regist(const std::string &classname, std::function<Component *(Args &&...args)> createFunc);
    Component *Create(const std::string &classname, Args &&...args);

private:
    ComponentFactory() {}

    static ComponentFactory *instance_;
    std::unordered_map<std::string, std::function<Component *(Args &&...args)>> map_;
};

template <typename... Args>
ComponentFactory<Args...> *ComponentFactory<Args...>::instance_ = nullptr;

template <typename... Args>
bool ComponentFactory<Args...>::Regist(const std::string &classname, std::function<Component *(Args &&...args)> createFunc)
{
    if (createFunc == nullptr)
        return false;

    bool ret = map_.insert(std::make_pair(classname, createFunc)).second;
    return ret;
}

template <typename... Args>
Component *ComponentFactory<Args...>::Create(const std::string &classname, Args &&...args)
{
    auto iter = map_.find(classname);
    if (iter == map_.end())
        return nullptr;
    return (iter->second(std::forward<Args>(args)...));
}

#endif