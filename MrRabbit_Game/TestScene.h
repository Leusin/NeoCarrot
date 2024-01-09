/// TestScene.h : ISccene 클래스를 상속받은 구현 클래스 입니다.
/// 
/// 씬마다 엔티티 매니저를 가지고 엔티티 생성, 실행, 삭제 등을 수행합니다.
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
    /// 미구현 함수
    /// 
    /// 다음 Scene을 가리키는 포인터
    /// 따라서 Scene은 링크드 리스트 형식
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<IScene> NextSene() override;

public:
    const std::string _name;

private:
    /// <summary>
    /// 현재 Scene이 시작하면서 생될 엔티티 목록을 나열합니다.
    /// </summary>
    void           CreateEnity();

    EntityManager* _entityManager;
};

} // namespace game