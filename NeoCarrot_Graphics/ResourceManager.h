/// ResourceManager.h : 그래픽스 엔진에서 메시 오브젝트의 리소스를 관리하는 매니저 클래스 입니다.
/// 모델들을 관리합니다.
/// 
/// 2024-01-11

#pragma once

#include "ModelEnum.h"
#include "ModelFactory.h"
#include "EntityManager.h"

#include <vector>
#include <memory>

namespace graphics
{

class ResourceManager
{
public:
    ResourceManager();

private:
	std::unique_ptr<core::EntityManager<ModelFactory>> _entityManager;
};
}