/// ResourceManager.h : �׷��Ƚ� �������� �޽� ������Ʈ�� ���ҽ��� �����ϴ� �Ŵ��� Ŭ���� �Դϴ�.
/// �𵨵��� �����մϴ�.
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