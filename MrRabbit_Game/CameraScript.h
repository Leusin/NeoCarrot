/// 2024-01-10

#pragma once

#include "EntityEnum.h"
#include "IComponent.h"

#include <memory>

 namespace core
 {
 template <typename T, typename U>
 class Entity;
 }
 
 using EntityPtr = std::shared_ptr<core::Entity<game::Tag, game::Layer>>;
 using EntityWeakPtr = std::weak_ptr<core::Entity<game::Tag, game::Layer>>;

namespace game
{

class Camera;

class CameraScript : public core::IComponent
{
public:
   /* CameraScript();*/
    CameraScript(EntityPtr entityPtr);
    ~CameraScript();

    void Update(float dt) override;

private:

    /// <summary>
    /// 컴포넌트를 소유하는 엔티티를 찾모하기 때문에
    /// shared_ptr 로 인한 메모리 누수를 고려하여
    /// waek_ptr 로 받는다
    /// </summary>
    EntityWeakPtr _entity{};

    Camera*   _camera{nullptr};
};

} // namespace game