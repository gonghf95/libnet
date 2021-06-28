#include "src/net/entity_system.h"

bool EntitySystem::Update()
{
    while(initializeSystems_.size() > 0)
    {
        auto pComponent = initializeSystems_.front();
        pComponent->Initialize();
        initializeSystems_.pop_front();

        const auto objUpdate = dynamic_cast<IUpdateSystem*>(pComponent);
        if(objUpdate!=nullptr)
            updateSystems_.push_back(objUpdate);
    }

    for(auto& iter : updateSystems_)
    {
        iter->Update();
    }

    return true;
}