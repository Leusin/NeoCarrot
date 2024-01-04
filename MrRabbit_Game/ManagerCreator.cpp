#include "ManagerCreator.h"
#include "IManager.h"

#include "SceneManager.h"
#include "ResourceManager.h"

#include <cassert>
#include <iostream>

std::unique_ptr<ge::IManager> ge::ManagerCreator::CreateManager(ManagerType&& managerType)
{
    printf("ManagerCreator\n");
	switch (managerType)
	{
	case ManagerType::Scene:
            printf("   SceneManager 持失...\n");
		return std::make_unique<SceneManager>();
		break;
	case ManagerType::Resource:
        printf("   ResourceManager 持失...\n");
        return std::make_unique<ResourceManager>();
		break;
	case ManagerType::Input:
		break;
	case ManagerType::Entity:
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
