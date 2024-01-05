#include "Vector3.h"
using namespace me;

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>::Vector3() = default;

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr me::Vector3<T>::Vector3(T x, T y, T z)
{
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr T Vector3<T>::LengthSq() const
{
    return Dot(*this);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr T Vector3<T>::Dot(const Vector3& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr T Vector3<T>::Cross(const Vector3& rhs) const
{
    return Vector3<T>((y * rhs.z) - (z * rhs.y), (z * rhs.x) - (x * rhs.z), (x * rhs.y) - (y * rhs.x));
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr Vector3<T> me::Vector3<T>::ComponentWiseMul(const Vector3& rhs) const
{
    return Vector3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

////////////////////////////////////////////////////////////
template <typename T>
inline constexpr Vector3<T> me::Vector3<T>::ComponentWiseDiv(const Vector3& rhs) const
{
    assert(rhs.x != 0 && "Vector3::cwiseDiv() 는 0으로 나눌 수 없습니다.");
    assert(rhs.y != 0 && "Vector3::cwiseDiv() 는 0으로 나눌 수 없습니다.");
    return Vector3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator-(const Vector3<T>& left)
{
    return Vector3<T>(-left.x, -left.y, -left.z);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;

    return left;
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator-(const Vector3<T>& left)
{
    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator*(const Vector3<T>& left, T right)
{
    return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator*(T left, const Vector3<T>& right)
{
    return Vector3<T>(right.x * left, right.y * left, right.z * left);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator*=(Vector3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator/(const Vector3<T>& left, T right)
{
    assert(right != 0 && "Vector3::operator/ 는 0으로 나눌 수 없습니다.");
    return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator/=(Vector3<T>& left, T right)
{
    assert(right != 0 && "Vector3::operator/= 는 0으로 나눌 수 없습니다.");
    left.x /= right;
    left.y /= right;
    left.z /= right;

    return left;
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}