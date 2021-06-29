#include "src/net/entity_system.h"
#include "src/net/test_entity.h"
#include "src/net/test_c_update.h"

#include <iostream>

int main(int argc, char *argv[])
{
    EntitySystem eSys;
    // auto pEntity1 = eSys.CreateComponent<TestEntityWithInitialAndUpdate>();
    auto pEntity2 = eSys.CreateComponent<TestEntityWithUpdate>();

    const auto pCUpdate = eSys.CreateComponent<TestCUpdate>();
    pEntity2->addComponent(pCUpdate);

    while(true)
    {
        eSys.Update();
    }

    return 0;
}