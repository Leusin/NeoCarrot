/// 2���� ���� ����ü �Դϴ�.
/// SFML �� �����Ͽ����ϴ�.
///
/// 2024-01-05

#pragma once

namespace math
{

template <typename T>
struct Matrix;

template <typename T>
struct Vector3
{
    T x{}; // ������ X ��ǥ
    T y{}; // ������ Y ��ǥ
    T z{}; // ������ Z ��ǥ

    /// <summary>
    /// �⺻ ������
    /// Vector3(0, 0, 0) �� �����մϴ�.
    /// </summary>
    constexpr Vector3();

    /// <summary>
    /// 3���� ��ǥ�� ������ �Դϴ�.
    /// </summary>
    /// <param name="x">������ X ��ǥ</param>
    /// <param name="y">������ Y ��ǥ</param>
    /// <param name="z">������ Z ��ǥ</param>
    constexpr Vector3(T x, T y, T z);

    /// <summary>
    /// �ٸ� Ÿ���� ���ͷκ��� ���ο� ���͸� �����մϴ�.
    ///
    /// U != T ���� �� ���� ȣ���ϴ� ���̱� ������,
    /// ���� ���� �����ڸ� ��ü�ϴ� ���� �ƴմϴ�.
    /// </summary>
    /// <typeparam name="U">�ٸ� Ÿ���� Vector3</typeparam>
    /// <param name="vector">��ȯ�� ����</param>
    template <typename U>
    constexpr explicit Vector3(const Vector3<U>& vector);

    // <summary>
    /// float �Ǵ� double Ÿ���� ������ ũ�⸦ ��ȯ�մϴ�.
    ///
    /// ���� ������ ���̰� �ʿ��� ���� �ƴ�
    /// �ٸ� ������ �ܼ� ���� �񱳸� �Ѵٸ�
    /// LengthSqrt() ����� �����մϴ�.
    /// </summary>
    T Length() const;

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
    [[nodiscard]] Vector3 Normalize() const;

    /// <summary>
    /// �� 3 ���� ������ ����
    /// </summary>
    constexpr T Dot(const Vector3& rhs) const;

    /// <summary>
    /// �� 3 ���� ������ ����
    /// </summary>
    constexpr Vector3<T> Cross(const Vector3& rhs) const;

    /// <summary>
    /// ������ �������� ���� ��(Component-wise multiplication)�� �����մϴ�.
    ///
    /// �ַ� ������ �����ϸ�(ũ�� ����) �۾����� ���˴ϴ�.
    /// ��������п��� '�Ƹ����� ��' �Ǵ� '���� ��'���� �˷����ֽ��ϴ�.
    /// </summary>
    /// <returns>(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z)</returns>
    constexpr Vector3 ComponentWiseMul(const Vector3& rhs) const;

    /// <summary>
    /// ������ ���� ���г��� ������(Component-wise division)�� �����մϴ�.
    ///
    /// �ַ� ������ �����ϸ�(ũ�� ����) �۾����� ���˴ϴ�.
    ///
    /// �� ������Ʈ ��� �����Ϳ��� �ȵ˴ϴ�.
    /// </summary>
    /// <returns>(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z)</returns>
    constexpr Vector3 ComponentWiseDiv(const Vector3& rhs) const;

    void MutiplyAdd(const Vector3& v1, const Vector3& v2, const Vector3& v3);

    Vector3<T> Vector3TransformNormal(const Matrix<T>& matrix) const;
};

/// <summary>
/// Vector3 ���� ������ - �����ε�
/// </summary>
/// <param name="rhs">�� ������ �ǿ�����</param>
/// <returns></returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator-(const Vector3<T>& right);

/// <summary>
///  Vector3 ���� ������ += �����ε�
///
/// �� ������ �ɹ��� ������ �����մϴ�.
/// �׸��� �װ���� ���� ���� �Ҵ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left�� ����</returns>
template <typename T>
constexpr Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right);

/// <summary>
/// Vector3 ���� ������ -= �����ε�
///
/// �� ������ �ɹ��� ������ �����մϴ�.
/// �׸��� �װ���� ���� ���� �Ҵ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left�� ����</returns>
template <typename T>
constexpr Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right);

/// <summary>
/// Vector3 ���� ������ + �����ε�
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>�� ������ �ɹ������� ����</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right);

/// <summary>
/// Vector3 ���� ������ - �����ε�
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>�� ������ �ɹ������� ����</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right);

/// <summary>
/// Vector3 ���� ������ * �����ε�
/// </summary>
/// <param name="left">���� �ǿ����� (��Į�� ��)</param>
/// <param name="right">������ �ǿ����� (����)</param>
/// <returns>right���� ����</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator*(const Vector3<T>& left, T right);

/// <summary>
/// Vector3 ���� ������ * �����ε�
/// </summary>
/// <param name="left">���� �ǿ����� (����)</param>
/// <param name="right">������ �ǿ����� (��Į�� ��)</param>
/// <returns>left���� ����</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator*(T left, const Vector3<T>& right);

/// <summary>
/// Vector3 ���� ������ *= �����ε�
///
/// ������ �ɹ���� left�� ���� �����մϴ�.
/// �׸��� �װ���� ���� ���� �Ҵ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ����� (����)</param>
/// <param name="right">������ �ǿ����� (��Į�� ��)</param>
/// <returns>left�� ����</returns>
template <typename T>
constexpr Vector3<T>& operator*=(Vector3<T>& left, T right);

/// <summary>
/// Vector3 ���� ������ / �����ε�
/// </summary>
/// <param name="left">���� �ǿ����� (����)</param>
/// <param name="right">������ �ǿ����� (��Į�� ��)</param>
/// <returns>left���� ������</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator/(const Vector3<T>& left, T right);

/// <summary>
/// Vector3 ���� ������ /= �����ε�
///
/// ������ �ɹ���� left�� �������� �����մϴ�.
/// �׸��� �װ���� ���� ���� �Ҵ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left�� ����</returns>
template <typename T>
constexpr Vector3<T>& operator/=(Vector3<T>& left, T right);

/// <summary>
///  Vector3 ���� ������ == �����ε�
///
/// �� ���͸� �ٱ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left �� right �� ���Ƹ� ��</returns>
template <typename T>
[[nodiscard]] constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right);

/// <summary>
///  Vector2 ���� ������ != �����ε�
///
/// �� ���͸� �ٱ��մϴ�.
/// </summary>
/// <param name="left">���� �ǿ�����</param>
/// <param name="right">������ �ǿ�����</param>
/// <returns>left �� right �� �ٸ��ٸ� ��</returns>
template <typename T>
[[nodiscard]] constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right);

} // namespace me

#include "Vector3.inl"