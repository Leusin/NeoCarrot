/// CameraManager : 카메라 개체를 위한 매니저
///
/// 2024-01-11

#pragma once

#include "EntityEnum.h"
#include "ForGraphics.h"

#include <memory>
#include <vector>

namespace core
{
template <typename T, typename U>
class Entity;
}

using WeakEntityPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace data
{
struct ForGraphics;
}

namespace game
{

class CameraManager
{
public:
    CameraManager();
    ~CameraManager();

    void GetCameraEntitys(std::vector<WeakEntityPtr> cameras);

    void GetActiveCameraInfo(data::ForGraphics* info);

    WeakEntityPtr GetActiveCamera();
private:

    std::vector<WeakEntityPtr> _cameras;
    data::CameraInfo           _camera;
};

} // namespace game