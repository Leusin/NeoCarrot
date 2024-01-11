/// ResourceManager.h : �׷��Ƚ� �������� �޽� ������Ʈ�� ���ҽ��� �����ϴ� �Ŵ��� Ŭ���� �Դϴ�.
/// �𵨵��� �����մϴ�.
///
/// 2024-01-11

#pragma once

#include "EntityManager.h"
#include "ModelEnum.h"
#include "ModelFactory.h"

#include <memory>
#include <vector>

namespace graphics
{
class ResourceManager;

class ModelManager
{
public:
    ModelManager(ResourceManager* resourceManager);

    void Initialize();
    void Update(float deltaTime);
    void Finalize();

private:
    void CreateEnity();

    std::unique_ptr<core::EntityManager<ModelFactory>> _entityManager;
};
} // namespace graphics