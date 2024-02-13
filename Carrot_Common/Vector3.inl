#pragma once


#include "Matrix.h"

#include <cassert>
#include <cmath>

namespace math
{

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T>::Vector3() = default;

//////////////////////////////////////////////////////////////////////
template<typename T>
inline constexpr Vector3<T>::Vector3(T x, T y, T z)
    : x(x)
    , y(y)
    , z(z)
{
}

//////////////////////////////////////////////////////////////////////
template<typename T>
inline T Vector3<T>::Length() const
{
    static_assert(std::is_floating_point_v<T>,
                  "Vector3::Length()는 부동소수점 타입만을 "
                  "지원합니다.\nVector3::Length() is only supported for "
                  "floating point types");

    return std::sqrt(x * x + y * y + z * z);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr T Vector3<T>::LengthSq() const
{
    return Dot(*this);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector3<T> Vector3<T>::Normalize() const
{
    assert(*this != Vector3<T>() &&
           "Vector3::Normalized()는 부동소수점 타입만을 "
           "지원합니다.\nVector3::Normalized() cannot normalize a zero "
           "vector");
    return (*this) / Length();
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr T Vector3<T>::Dot(const Vector3& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T> Vector3<T>::Cross(const Vector3& rhs) const
{
    return Vector3<T>{ (y * rhs.z) - (z * rhs.y),
                       (z * rhs.x) - (x * rhs.z),
                       (x * rhs.y) - (y * rhs.x) };
}

//////////////////////////////////////////////////////////////////////
template<typename T>
inline constexpr Vector3<T> math::Vector3<T>::ComponentWiseMul(const Vector3& rhs) const
{
    return Vector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
inline constexpr Vector3<T> math::Vector3<T>::ComponentWiseDiv(const Vector3& rhs) const
{
    assert(rhs.x != 0 && "Vector3::cwiseDiv() 는 0으로 나눌 수 없습니다.");
    assert(rhs.y != 0 && "Vector3::cwiseDiv() 는 0으로 나눌 수 없습니다.");
    return Vector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
inline void Vector3<T>::MutiplyAdd(const Vector3& v1,
                                   const Vector3& v2,
                                   const Vector3& v3)
{
    x = v1.x * v2.x + v3.x;
    y = v1.y * v2.y + v3.y;
    z = v1.z * v2.z + v3.z;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
inline Vector3<T> Vector3<T>::Vector3TransformNormal(const Matrix<T>& matrix) const
{
    Vector3 result;

    result.x = x * matrix._data[0][0] + y * matrix._data[1][0] +
               z * matrix._data[2][0];
    result.y = x * matrix._data[0][1] + y * matrix._data[1][1] +
               z * matrix._data[2][1];
    result.z = x * matrix._data[0][2] + y * matrix._data[1][2] +
               z * matrix._data[2][2];

    return result;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T> operator-(const Vector3<T>& left)
{
    return Vector3<T>(-left.x, -left.y, -left.z);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;

    return left;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T> operator*(const Vector3<T>& left, T right)
{
    return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T> operator*(T left, const Vector3<T>& right)
{
    return Vector3<T>(right.x * left, right.y * left, right.z * left);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T>& operator*=(Vector3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T> operator/(const Vector3<T>& left, T right)
{
    assert(right != 0 && "Vector3::operator/ 는 0으로 나눌 수 없습니다.");
    return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr Vector3<T>& operator/=(Vector3<T>& left, T right)
{
    assert(right != 0 && "Vector3::operator/= 는 0으로 나눌 수 없습니다.");
    left.x /= right;
    left.y /= right;
    left.z /= right;

    return left;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

//////////////////////////////////////////////////////////////////////
template<typename T>
constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}

} // namespace math