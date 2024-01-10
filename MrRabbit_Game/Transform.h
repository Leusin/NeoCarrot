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

    math::Vector3<float> GetPosition() const;
    math::Vector3<float> GetRight() const;
    math::Vector3<float> GetLook() const;
    math::Vector3<float> GetUp() const;

    void SetPosition(const math::Vector3<float>& val);
    void SetRight(const math::Vector3<float>& val);
    void SetLook(const math::Vector3<float>& val);
    void SetUp(const math::Vector3<float>& val);

private:
    // ��ġ
    math::Vector3<float> _position{0.0f, 0.0f, 0.0f};

    // ���� ����
    math::Vector3<float> _right{1.0f, 0.0f, 0.0f}; // x
    math::Vector3<float> _up{0.0f, 1.0f, 0.0f};    // y
    math::Vector3<float> _look{0.0f, 0.0f, 1.0f};  // z

    // ��ȯ ���
    math::Matrix<float> _translation;
    math::Matrix<float> _rotation;
    math::Matrix<float> _scale;

    // ���� ��ȯ��� 
    math::Matrix<float> _tranceformMatreix;
};

} // namespace game