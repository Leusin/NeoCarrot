///
/// 2024-01-09

#pragma once

#include "IComponent.h"
#include "Vector3.h"
#include "Matrix.h"

namespace game
{

class Transform : public core::IComponent
{
public:
    Transform();
    ~Transform();

    math::Vector3<float> GetPosition();
    math::Vector3<float> GetRight();

private:
    // ��ġ
    math::Vector3<float> _position{0.0f, 0.0f, 0.0f};

    // ���� ����
    math::Vector3<float> _right{1.0f, 0.0f, 0.0f}; // x
    math::Vector3<float> _up{0.0f, 1.0f, 0.0f};    // y
    math::Vector3<float> _look{0.0f, 0.0f, 1.0f};  // z

    // ��ȯ ���
    math::Matrix _translation;
    math::Matrix _rotation;
    math::Matrix _scale;

    // ���� ��ȯ��� 
    math::Matrix _tranceformMatreix;
};

} // namespace game