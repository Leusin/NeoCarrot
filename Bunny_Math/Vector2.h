/// 2���� ���� ����ü �Դϴ�.
/// SFML �� �����Ͽ����ϴ�.
/// 
/// 2024-01-05

#pragma once

namespace math
{
/// <summary>
/// 2���� �ٷ�� ���� ���ø� Ŭ���� ����ü
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
struct Vector2
{
    T x{}; // ������ X ��ǥ
    T y{}; // ������ Y ��ǥ
    
    /// <summary>
    /// �⺻ ������
    /// Vector2(0, 0) �� �����մϴ�.
    /// </summary>
    constexpr Vector2();

    /// <summary>
    /// 2���� ��ǥ�� ������ �Դϴ�..
    /// </summary>
    /// <param name="x">������ X ��ǥ</param>
    /// <param name="y">������  Y ��ǥ</param>
    constexpr Vector2(T x, T y);

    /// <summary>
    /// �ٸ� Ÿ���� ���ͷκ��� ���ο� ���͸� �����մϴ�.
    /// 
    /// U != T ���� �� ���� ȣ���ϴ� ���̱� ������,
    /// ���� ���� �����ڸ� ��ü�ϴ� ���� �ƴմϴ�.
    /// </summary>
    /// <typeparam name="U">�ٸ� Ÿ���� Vector2</typeparam>
    /// <param name="vector">��ȯ�� ����</param>
    template <typename U>
    constexpr explicit Vector2(const Vector2<U>& vector);

    /// <summary>
    /// float �Ǵ� double Ÿ���� ������ ũ�⸦ ��ȯ�մϴ�.
    /// 
    /// ���� ������ ���̰� �ʿ��� ���� �ƴ�
    /// �ٸ� ������ �ܼ� ���� �񱳸� �Ѵٸ�
    /// LengthSqrt() ����� �����մϴ�.
    /// </summary>
    constexpr T Length() const;

    /// <summary>
    /// ���� ũ�Ⳣ�� ���� �񱳰� �ʿ��� ��, �ַ� ����մϴ�.
    /// </summary>
    /// <returns></returns>
    constexpr T LengthSq() const;

    /// <summary>
    /// ���� ���������� ũ�� 1�� ����ȭ �մϴ�.
    /// 
    /// *this �� �� ���Ϳ����� �ȵ˴ϴ�.
    /// </summary>
    /// <returns></returns>
    [[nodiscard]] Vector2 Normalize() const;

    /// <summary>
    ///  float �Ǵ� double Ÿ������ ���� ���͸� ���� ���Ϳ� �������� ���� ��ȯ�մϴ�.
    /// 
    /// �࿡ ���͸� �����մϴ�. ����ȭ�� �ʿ� �����ϴ�.
    /// ���� ���̴� o�̿��� �ȵ˴ϴ�.
    /// </summary>
    /// <param name="axis"></param>
    /// <returns></returns>
    Vector2 ProjectedOnto(const Vector2& axis) const;

    /// <summary>
    /// ���� ���Ϳ��� ������ ���͸� ��ȯ�մϴ�.
    /// 
    /// �ǿ����ڸ� 3D ���ͷ� �����Ͽ� ���� ���� ����մϴ�.
    /// </summary>
    /// <returns>z ������ ��ȯ�մϴ�.(x ��  y ������ �׻� 0)</returns>
    constexpr Vector2 Perpendicular() const;

    /// <summary>
    /// �� 2 ���� ������ ����
    /// </summary>
    constexpr T Dot(const Vector2& rhs) const;

    /// <summary>
    /// �� 2 ���� ������ ����
    /// </summary>
    constexpr T Cross(const Vector2& rhs) const;

    /// <summary>
    /// ������ �������� ���� ��(Component-wise multiplication)�� �����մϴ�.
    /// 
    /// �ַ� ������ �����ϸ�(ũ�� ����) �۾����� ���˴ϴ�.
    /// ��������п��� '�Ƹ����� ��' �Ǵ� '���� ��'���� �˷����ֽ��ϴ�.
    /// </summary>
    /// <returns>(lhs.x*rhs.x, lhs.y*rhs.y)</returns>
    constexpr Vector2 ComponentWiseMul(const Vector2& rhs) const;

    /// <summary>
    /// ������ ���� ���г��� ������(Component-wise division)�� �����մϴ�.
    /// 
    /// �ַ� ������ �����ϸ�(ũ�� ����) �۾����� ���˴ϴ�.
    /// 
    /// �� ������Ʈ ��� �����Ϳ��� �ȵ˴ϴ�.
    /// </summary>
    /// <returns>(lhs.x/rhs.x, lhs.y/rhs.y)</returns>
    constexpr Vector2 ComponentWiseDiv(const Vector2& rhs) const;
};

/// <summary>
/// Vector2 ���� ������ - �����ε�
/// </summary>
/// <param name="rhs">�� ������ �ǿ�����</param>
/// <returns></returns>
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T>& left);

/// <summary>
///  Vector2 ���� ������ += �����ε�
/// 
/// �� ������ �ɹ��� ������ �����մϴ�.
/// �׸��� �װ���� ���� ���� �Ҵ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left�� ����</returns>
template <typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right);

/// <summary>
/// Vector2 ���� ������ -= �����ε�
/// 
/// �� ������ �ɹ��� ������ �����մϴ�.
/// �׸��� �װ���� ���� ���� �Ҵ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left�� ����</returns>
template <typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right);

/// <summary>
/// Vector2 ���� ������ + �����ε�
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>�� ������ �ɹ������� ����</returns>
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right);

/// <summary>
/// Vector2 ���� ������ - �����ε�
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>�� ������ �ɹ������� ����</returns>
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right);

/// <summary>
/// Vector2 ���� ������ * �����ε�
/// </summary>
/// <param name="left">���� �ǿ����� (��Į�� ��)</param>
/// <param name="right">������ �ǿ����� (����)</param>
/// <returns>right���� ����</returns>
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator*(const Vector2<T>& left, T right);

/// <summary>
/// Vector2 ���� ������ * �����ε�
/// </summary>
/// <param name="left">���� �ǿ����� (����)</param>
/// <param name="right">������ �ǿ����� (��Į�� ��)</param>
/// <returns>left���� ����</returns>
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator*(T left, const Vector2<T>& right);

/// <summary>
/// Vector2 ���� ������ *= �����ε�
///
/// ������ �ɹ���� left�� ���� �����մϴ�.
/// �׸��� �װ���� ���� ���� �Ҵ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ����� (����)</param>
/// <param name="right">������ �ǿ����� (��Į�� ��)</param>
/// <returns>left�� ����</returns>
template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& left, T right);

/// <summary>
/// Vector2 ���� ������ / �����ε�
/// </summary>
/// <param name="left">���� �ǿ����� (����)</param>
/// <param name="right">������ �ǿ����� (��Į�� ��)</param>
/// <returns>left���� ������</returns>
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator/(const Vector2<T>& left, T right);

/// <summary>
/// Vector2 ���� ������ /= �����ε�
///
/// ������ �ɹ���� left�� �������� �����մϴ�.
/// �׸��� �װ���� ���� ���� �Ҵ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left�� ����</returns>
template <typename T>
constexpr Vector2<T>& operator/=(Vector2<T>& left, T right);

/// <summary>
///  Vector2 ���� ������ == �����ε�
///
/// �� ���͸� �ٱ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left �� right �� ���Ƹ� ��</returns>
template <typename T>
[[nodiscard]] constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right);

/// <summary>
///  Vector2 ���� ������ != �����ε�
///
/// �� ���͸� �ٱ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left �� right �� �ٸ��ٸ� ��</returns>
template <typename T>
[[nodiscard]] constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right);

} // namespace me

#include "Vector2.inl"