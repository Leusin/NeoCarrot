#pragma once

#include <array>

namespace math
{
template <typename T>
struct Vector3;

template <typename T>
struct Matrix
{
    std::array<std::array<T, 4>, 4> _data;

    Matrix();
    void Identity();
    void RotateAxis(const Vector3<float>& axis, const float& angle);
    void RotateAxisNormal(const Vector3<float>& axis, const float& angle);

    void RotateY(const float& angle);

private:
    const int _rows = 4;
    const int _columns = 4;
};

} // namespace math

#include "Matrix.inl"