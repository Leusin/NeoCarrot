///
/// �ʿ��� ���� ���� �Լ����� �ζ��� �Լ��� ����(wrapping) �Ǿ� �ֽ��ϴ�.
///

#pragma once

#include <cmath>

namespace math
{

// �� ������ �ڸ��� �ٲٴ� �Լ�
inline void Swap(float& lhs, float& rhs)
{
    const float temp = lhs;
    lhs              = rhs;
    rhs              = temp;
}

/// <summary>
/// �ε� �Ҽ����� ���ϴ� �� ���:
/// ��ǻ���� �ε� �Ҽ����� ������ ���� �񱳰� ��Ʊ� ������
/// �� �Ǽ� ���� ���� �������� �Ǵ��ϴ� �� ����մϴ�.
/// </summary>
/// <param name="lhs">���� flaot �� 1</param>
/// <param name="rhs">���� float �� 2</param>
/// <param name="epsilon">���� ��� ����</param>
inline bool FuzzyRealEqual(const float& lhs, const float& rhs, const float& epsilon /* = Constant::FLOAT_TOLERANCE*/);

/// <summary>
/// �ε� �Ҽ����� ��
/// </summary>
/// <param name="lhs">���� flaot �� 1</param>
/// <param name="rhs">���� float �� 2</param>
inline bool IsEqual(const float& lhs, const float& rhs);

/// ȣ����
// ��(��)���� ����(rad)����
inline float DegreeToRadian(const float angle);

// ����(rad)���� ��(��)��
inline float RadianToDegree(const float angle);

} // namespace me