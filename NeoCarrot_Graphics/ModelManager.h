/// ResourceManager.h : 그래픽스 엔진에서 메시 오브젝트의 리소스를 관리하는 매니저 클래스 입니다.
/// 모델들을 관리합니다.
///
/// 2024-01-11

#pragma once

#include "EntityManager.h"
#include "ModelFactory.h"

#include <memory>
#include <vector>

namespace graphics
{
class D3D11Context_mk2;
class Camera3D;

class ModelManager
{
public:
    ModelManager(D3D11Context_mk2* d3dcontext, Camera3D* camera);

    void Initialize();
    void Update(float deltaTime);
    void Finalize();

private:
    void CreateEnity();

    std::unique_ptr<core::EntityManager<ModelFactory>> _entityManager;
};
} // namespace graphics