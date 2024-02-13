#pragma once

#include "Matrix.h"
#include "Vector3.h"

namespace data
{

struct CameraInfo
{
    math::Vector3<float> _position{0.0f, 0.0f, 0.0f};

    math::Vector3<float> _right{1.0f, 0.f, 0.f};
    math::Vector3<float> _up{0.0f, 1.f, 0.f};
    math::Vector3<float> _look{0.0f, 0.f, 1.f};

    float _nearZ{ 000.1f };
    float _farZ{ 1000.f };
    float _fovY{ 0.25f };

    math::Matrix<float> _view;
    //math::Matrix<float> _proj;
};

 }