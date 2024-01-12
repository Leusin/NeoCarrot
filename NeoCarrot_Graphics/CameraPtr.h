#pragma once

#include "EntityEnum.h"
#include "IComponent.h"

#include <memory>

namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{
class Camera3D;
class Transpose;

class CameraPtr : public core::IComponent
{
public:
    CameraPtr(EntityPtr entityPtr, Camera3D* camera);

    void Update(float dt) override;

private:
    EntityWeakPtr _entity;
    Transpose* _transpose;
    Camera3D*  _camera;
};

} // namespace graphics