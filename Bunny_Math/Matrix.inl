#pragma once

#include "Vector3.h"

#include <cmath>
#include "Matrix.h"

namespace math
{

template <typename T>
inline Matrix<T>::Matrix()
{
    Identity();
}

template <typename T>
inline void Matrix<T>::Identity()
{
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _columns; ++j)
        {
            _data[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

template <typename T>
inline void Matrix<T>::RotateAxis(const Vector3<float>& axis, const float& angle)
{
    // 축 벡터 정규화
    Vector3<float> a = axis.Normalize();

    // sin 과 cos
    float s = std::sin(angle);
    float c = std::cos(angle);

    // 1 - cos(angle)
    float oneMinusCos = 1.0f - c;

    // 회전 행렬 계산
    _data[0][0] = c + a.x * a.x * oneMinusCos;
    _data[0][1] = a.x * a.y * oneMinusCos + a.z * s;
    _data[0][2] = a.x * a.z * oneMinusCos - a.y * s;

    _data[1][0] = a.y * a.x * oneMinusCos - a.z * s;
    _data[1][1] = c + a.y * a.y * oneMinusCos;
    _data[1][2] = a.y * a.z * oneMinusCos + a.x * s;

    _data[2][0] = a.z * a.x * oneMinusCos + a.y * s;
    _data[2][1] = a.z * a.y * oneMinusCos - a.x * s;
    _data[2][2] = c + a.z * a.z * oneMinusCos;
}

template <typename T>
inline void Matrix<T>::RotateAxisNormal(const Vector3<float>& axis, const float& angle)
{
    // sin 과 cos
    float s = std::sin(angle);
    float c = std::cos(angle);

    // 1 - cos(angle)
    float oneMinusCos = 1.0f - c;

    // 회전 행렬 계산
    _data[0][0] = c + axis.x * axis.x * oneMinusCos;
    _data[0][1] = axis.x * axis.y * oneMinusCos + axis.z * s;
    _data[0][2] = axis.x * axis.z * oneMinusCos - axis.y * s;

    _data[1][0] = axis.y * axis.x * oneMinusCos - axis.z * s;
    _data[1][1] = c + axis.y * axis.y * oneMinusCos;
    _data[1][2] = axis.y * axis.z * oneMinusCos + axis.x * s;

    _data[2][0] = axis.z * axis.x * oneMinusCos + axis.y * s;
    _data[2][1] = axis.z * axis.y * oneMinusCos - axis.x * s;
    _data[2][2] = c + axis.z * axis.z * oneMinusCos;
}

template <typename T>
inline void Matrix<T>::RotateY(const float& angle)
{
    float cosTheta = std::cos(angle);
    float sinTheta = std::sin(angle);

    _data[0][0] = cosTheta;
    _data[0][2] = sinTheta;
    _data[2][0] = -sinTheta;
    _data[2][2] = cosTheta;
}

template <typename T>
inline std::array<T, 4>& Matrix<T>::operator[](int index)
{
    return _data[index];
}

template <typename T>
inline const std::array<T, 4>& Matrix<T>::operator[](int index) const
{
    return _data[index];
}

} // namespace math