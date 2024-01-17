/// TestScene.h : ISccene 클래스를 상속받은 구현 클래스 입니다.
///
///    - 엔티티 매니저: 가지고 엔티티 생성, 실행, 삭제 등을 수행합니다.
///
///    - 카메라 매니저: 카메라 태그를 가진 개체만을 관리합니다.
///    그래픽스에게 필요한 카메라 정보를 넘깁니다.
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
    /// 미구현 함수
    ///
    /// 다음 Scene을 가리키는 포인터
    /// 따라서 Scene은 링크드 리스트 형식
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<IScene> NextSene() override;

public:

    /// <summary>
    /// Scene의 이름
    /// </summary>
    const std::string _name;

private:
    /// <summary>
    /// 현재 Scene이 시작하면서 생될 엔티티 목록을 나열합니다.
    /// </summary>
    void CreateEnity();

    void InitCameraManager();

    core::EntityManager<EntityFactory>* _entityManager;
};

} // namespace game