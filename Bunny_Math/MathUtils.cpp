#include "MathUtils.h"
#include "Constants.h"

bool me::FuzzyRealEqual(const float& lhs, const float& rhs, const float& epsilon)
{
    return std::fabs(lhs - rhs) < epsilon;
}

bool me::IsEqual(const float& lhs, const float& rhs)
{
    return FuzzyRealEqual(lhs, rhs, Constant::FLOAT_TOLERANCE);
}

float me::DegreeToRadian(const float angle)
{
    return angle * Constant::PI / 180.f;
}

float me::RadianToDegree(const float angle)
{
    return angle * 180.f / Constant::PI;
}
