#include "MathUtils.h"
#include "Constants.h"

bool me::fuzzyRealEqual(const float& lhs, const float& rhs, const float& epsilon)
{
    return std::fabs(lhs - rhs) < epsilon;
}

bool me::isEqual(const float& lhs, const float& rhs)
{
    return fuzzyRealEqual(lhs, rhs, Constant::FLOAT_TOLERANCE);
}

float me::DEGREE_TO_RADIAN(const float angle)
{
    return angle * Constant::PI / 180.f;
}

float me::RADIAN_TO_DEGREE(const float angle)
{
    return angle * 180.f / Constant::PI;
}
