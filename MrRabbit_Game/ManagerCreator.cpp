#include "ManagerCreator.h"

#include "IManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "EntityManager.h"

#include <cassert>

std::unique_ptr<game::IManager> game::ManagerCreator::CreateManager(ManagerType&& managerType)
{

    switch (managerType)
    {
        case ManagerType::Scene:
            return std::make_unique<SceneManager>();
            break;
        case ManagerType::Resource:
            return std::make_unique<ResourceManager>();
            break;
        case ManagerType::Input:
            break;
        case ManagerType::Entity:
            return std::make_unique<EntityManager>();
            break;
        case ManagerType::Audio:
            break;
        case ManagerType::Event:
            break;
        case ManagerType::Time:
            break;
        case ManagerType::UI:
            break;
        default:
            assert(false);
            break;
    }

    return nullptr;
}
