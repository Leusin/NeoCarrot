/// 2024-01-15

#pragma once

namespace math
{
template <typename T>
struct Vector4
{
    T x{}; // ������ X ��ǥ
    T y{}; // ������ Y ��ǥ
    T z{}; // ������ Z ��ǥ
    T w{}; // ������ w ��ǥ

    constexpr Vector4() = default;

    /// <summary>
    /// 4���� ��ǥ�� ������ �Դϴ�.
    /// </summary>
    /// <param name="x">������ X ��ǥ</param>
    /// <param name="y">������ Y ��ǥ</param>
    /// <param name="z">������ Z ��ǥ</param>
    /// <param name="z">������ W ��ǥ</param>
    constexpr Vector4(T x, T y, T z, T w);
};

template <typename T>
inline constexpr Vector4<T>::Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
{
}

} // namespace math

#include "Vector4.inl"