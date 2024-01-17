/// TestScene.h : ISccene Ŭ������ ��ӹ��� ���� Ŭ���� �Դϴ�.
///
///    - ��ƼƼ �Ŵ���: ������ ��ƼƼ ����, ����, ���� ���� �����մϴ�.
///
///    - ī�޶� �Ŵ���: ī�޶� �±׸� ���� ��ü���� �����մϴ�.
///    �׷��Ƚ����� �ʿ��� ī�޶� ������ �ѱ�ϴ�.
///
/// 2024-01-09

#pragma once

#include "IScene.h"
#include "EntityManager.h"

#include <string>
#include <vector>

namespace game
{
class EntityFactory;

class TestScene : public IScene
{
public:
    TestScene(core::EntityManager<EntityFactory>* entityManager);
    ~TestScene();

public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Finalize() override;

    void ExportData(data::ForGraphics* info) override;

    /// <summary>
    /// �̱��� �Լ�
    ///
    /// ���� Scene�� ����Ű�� ������
    /// ���� Scene�� ��ũ�� ����Ʈ ����
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<IScene> NextSene() override;

public:

    /// <summary>
    /// Scene�� �̸�
    /// </summary>
    const std::string _name;

private:
    /// <summary>
    /// ���� Scene�� �����ϸ鼭 ���� ��ƼƼ ����� �����մϴ�.
    /// </summary>
    void CreateEnity();

    void InitCameraManager();

    core::EntityManager<EntityFactory>* _entityManager;
};

} // namespace game