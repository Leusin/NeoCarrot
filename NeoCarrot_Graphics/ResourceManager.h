/// ResourceManager.h : �׷��Ƚ� �������� �޽� ������Ʈ�� ���ҽ��� �����ϴ� �Ŵ��� Ŭ���� �Դϴ�.
/// �𵨵��� �����մϴ�.
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