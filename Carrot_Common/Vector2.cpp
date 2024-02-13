#include "Vector2.h"
#include <cassert>
#include <cmath>

namespace math
{
//////////////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> Vector2<T>::Normalize() const
{
    static_assert(std::is_floating_point_v<T>,
                  "Vector2::Normalized()는 부동소수점 타입만을 지원합니다.\nVector2::Normalized() is only supported "
                  "for floating point types");

    assert(*this != Vector2<T>() &&
           "Vector2::Normalized()는 영벡터를 정규화를 수행할 수 없습니다.\nVector2::Normalized() cannot normalize a "
           "zero vector");

    return (*this) / Length();
}

//////////////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::ProjectedOnto(const Vector2& axis) const
{
    static_assert(std::is_floating_point_v<T>, "Vector2::projectedOnto() 는 부동소수점 타입만을 지원합니다.\nVector2::projectedOnto() is only supported for floating point types");

    assert(axis != Vector2<T>() && "Vector2::projectedOnto()는 영벡터를 정사형 수행할 수 없습니다.\nVector2::projectedOnto() cannot project onto a zero vector");
    return Dot(axis) / axis.LengthSq() * axis;
}

} // namespace me