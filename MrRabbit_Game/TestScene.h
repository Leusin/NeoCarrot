/// TestScene.h : ISccene Ŭ������ ��ӹ��� ���� Ŭ���� �Դϴ�.
/// 
/// ������ ��ƼƼ �Ŵ����� ������ ��ƼƼ ����, ����, ���� ���� �����մϴ�.
/// 
/// 2024-01-09

#pragma once

#include "IScene.h"

#include <string>
#include <vector>

namespace game
{
class EntityManager;

class TestScene : public IScene
{
public:
    TestScene(EntityManager* entityManager);
    ~TestScene();

public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Finalize() override;


    /// <summary>
    /// �̱��� �Լ�
    /// 
    /// ���� Scene�� ����Ű�� ������
    /// ���� Scene�� ��ũ�� ����Ʈ ����
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<IScene> NextSene() override;

public:
    const std::string _name;

private:
    /// <summary>
    /// ���� Scene�� �����ϸ鼭 ���� ��ƼƼ ����� �����մϴ�.
    /// </summary>
    void           CreateEnity();

    EntityManager* _entityManager;
};

} // namespace game