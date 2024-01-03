#include "ManagerCreator.h"
#include "IManager.h"
#include "SceneManager.h"

#include <cassert>

std::unique_ptr<ge::IManager> ge::ManagerCreator::CreateManager(ManagerType&& managerType)
{
	switch (managerType)
	{
	case ManagerType::Scene:
		return std::make_unique<SceneManager>();
		break;
	case ManagerType::Resource:
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
