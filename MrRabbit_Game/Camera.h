///
/// 2024-01-09

#pragma once

#include "../UnityLike_Core/IComponent.h"
#include "../Bunny_Math/Vector3.h"

namespace game
{

class Camera : public core::IComponent
{
public:
    Camera();
    ~Camera();


    me::Vector3<float> _position{0.0f, 0.0f, 0.0f};
    me::Vector3<float> _right{1.0f, 0.0f, 0.0f}; // x
    me::Vector3<float> _up{0.0f, 1.0f, 0.0f};    // y
    me::Vector3<float> _look{0.0f, 0.0f, 1.0f};  // z
};

} // namespace game