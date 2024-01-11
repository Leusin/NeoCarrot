/// ResourceManager.h : 그래픽스 엔진에서 메시 오브젝트의 리소스를 관리하는 매니저 클래스 입니다.
/// 모델들을 관리합니다.
/// 
/// 2024-01-11

#pragma once

#include "ModelEnum.h"

#include <vector>
#include <memory>

namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr     = std::shared_ptr<core::Entity<grahics::Tag, grahics::Layer>>;
using WeakEntityPtr = std::weak_ptr<core::Entity<grahics::Tag, grahics::Layer>>;

namespace grahics
{

class ResourceManager
{


private:
	std::vector<EntityPtr>         _entities;
};

}