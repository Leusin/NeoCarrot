#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <memory>

namespace graphics
{
class Camera3D;
class Transpose;

class CameraPtr : public core::IComponent, virtual core::GetEntity
{
public:
    CameraPtr(EntityPtr entityPtr, Camera3D* camera);

    void Update(float dt) override;

private:
    Transpose* _transpose{ nullptr };
    Camera3D*  _camera{ nullptr };
};

} // namespace graphics