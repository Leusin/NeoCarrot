/// 2024-01-15

#pragma once

namespace math
{
template <typename T>
struct Vector4
{
    T x{}; // º¤ÅÍÀÇ X ÁÂÇ¥
    T y{}; // º¤ÅÍÀÇ Y ÁÂÇ¥
    T z{}; // º¤ÅÍÀÇ Z ÁÂÇ¥
    T w{}; // º¤ÅÍÀÇ w ÁÂÇ¥

    constexpr Vector4() = default;

    /// <summary>
    /// 4Â÷¿ø ÁÂÇ¥°è »ý¼ºÀÚ ÀÔ´Ï´Ù.
    /// </summary>
    /// <param name="x">º¤ÅÍÀÇ X ÁÂÇ¥</param>
    /// <param name="y">º¤ÅÍÀÇ Y ÁÂÇ¥</param>
    /// <param name="z">º¤ÅÍÀÇ Z ÁÂÇ¥</param>
    /// <param name="z">º¤ÅÍÀÇ W ÁÂÇ¥</param>
    constexpr Vector4(T x, T y, T z, T w);
};

template <typename T>
inline constexpr Vector4<T>::Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
{
}

} // namespace math

#include "Vector4.inl"