#include "Vector3.h"

#include <cassert>
#include <cmath>

namespace me
{

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::Length() const
{
    static_assert(std::is_floating_point_v<T>,
                  "Vector3::Length()는 부동소수점 타입만을 지원합니다.\nVector3::Length() is only supported for "
                  "floating point types");

    return std::sqrt(x * x + y * y + z * z);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> Vector3<T>::Normalize() const
{
    assert(*this != Vector3<T>() &&
           "Vector3::Normalized()는 부동소수점 타입만을 지원합니다.\nVector3::Normalized() cannot normalize a zero "
           "vector");
    return (*this) / Length();
}

} // namespace me

#include "Vector3.inl"