#pragma once

#include <cmath>
#include <cassert>
#include <xtr1common>

namespace math
{

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr Vector2<T>::Vector2() = default;

template <typename T>
inline constexpr Vector2<T>::Vector2(T x, T y) : x(x), y(y)
{
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
inline constexpr Vector2<T>::Vector2(const Vector2<U>& vector) :
x(static_cast<T>(vector.x)),
y(static_cast<T>(vector.y))
{
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr T Vector2<T>::Length() const
{

    static_assert(std::is_floating_point_v<T>,
                  "Vector2::length()는 부동소수점 타입만을 지원합니다.\nVector2::length() is only supported for "
                  "floating point types");

    // don't use std::hypot because of slow performance
    return std::sqrt(x * x + y * y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr T Vector2<T>::LengthSq() const
{
    return T();
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr Vector2<T> Vector2<T>::Perpendicular() const
{
    return Vector2<T>(-y, x);
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr T Vector2<T>::Dot(const Vector2& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr T Vector2<T>::Cross(const Vector2& rhs) const
{
    return x * rhs.y - y * rhs.x;
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr Vector2<T> Vector2<T>::ComponentWiseMul(const Vector2& rhs) const
{
    return Vector2<T>(x * rhs.x, y * rhs.y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr Vector2<T> Vector2<T>::ComponentWiseDiv(const Vector2& rhs) const
{
    assert(rhs.x != 0 && "Vector2::cwiseDiv() 는 0으로 나눌 수 없습니다.");
    assert(rhs.y != 0 && "Vector2::cwiseDiv() 는 0으로 나눌 수 없습니다.");
    return Vector2<T>(x / rhs.x, y / rhs.y);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator-(const Vector2<T>& right)
{
    return Vector2<T>(-right.x, -right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}

template <typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x + right.x, left.y + right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x - right.x, left.y - right.y);
}
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator*(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x * right, left.y * right);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator*(T left, const Vector2<T>& right)
{
    return Vector2<T>(right.x * left, right.y * left);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;

    return left;
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator/(const Vector2<T>& left, T right)
{
    assert(right != 0 && "Vector2::operator/ 는 0으로 나눌 수 없습니다.");
    return Vector2<T>(left.x / right, left.y / right);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator/=(Vector2<T>& left, T right)
{
    assert(right != 0 && "Vector2::operator/= 는 0으로 나눌 수 없습니다.");
    left.x /= right;
    left.y /= right;

    return left;
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x != right.x) || (left.y != right.y);
}

} // namespace me