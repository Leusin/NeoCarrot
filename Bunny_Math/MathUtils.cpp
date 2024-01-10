#include "MathUtils.h"
#include "Constants.h"

bool math::FuzzyRealEqual(const float& lhs, const float& rhs, const float& epsilon)
{
    return std::fabs(lhs - rhs) < epsilon;
}

bool math::IsEqual(const float& lhs, const float& rhs)
{
    return FuzzyRealEqual(lhs, rhs, Constant::FLOAT_TOLERANCE);
}

float math::DegreeToRadian(const float angle)
{
    return angle * Constant::PI / 180.f;
}

float math::RadianToDegree(const float angle)
{
    return angle * 180.f / Constant::PI;
}
