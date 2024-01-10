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
    /// ������Ʈ�� �����ϴ� ��ƼƼ�� ã���ϱ� ������
    /// shared_ptr �� ���� �޸� ������ ����Ͽ�
    /// waek_ptr �� �޴´�
    /// </summary>
    EntityWeakPtr _entity{};

    Camera*   _camera{nullptr};
};

} // namespace game