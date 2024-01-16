/// 2차원 벡터 구조체 입니다.
/// SFML 을 참고하였습니다.
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
    T x{}; // 벡터의 X 좌표
    T y{}; // 벡터의 Y 좌표
    T z{}; // 벡터의 Z 좌표

    /// <summary>
    /// 기본 생성자
    /// Vector3(0, 0, 0) 을 생성합니다.
    /// </summary>
    constexpr Vector3();

    /// <summary>
    /// 3차원 좌표계 생성자 입니다.
    /// </summary>
    /// <param name="x">벡터의 X 좌표</param>
    /// <param name="y">벡터의 Y 좌표</param>
    /// <param name="z">벡터의 Z 좌표</param>
    constexpr Vector3(T x, T y, T z);

    /// <summary>
    /// 다른 타입의 벡터로부터 새로운 벡터를 생성합니다.
    ///
    /// U != T 조건 일 때만 호출하는 것이기 때문에,
    /// 절대 복사 생성자를 대체하는 것이 아닙니다.
    /// </summary>
    /// <typeparam name="U">다른 타입의 Vector3</typeparam>
    /// <param name="vector">변환된 벡터</param>
    template <typename U>
    constexpr explicit Vector3(const Vector3<U>& vector);

    // <summary>
    /// float 또는 double 타입인 벡터의 크기를 반환합니다.
    ///
    /// 실제 벡터의 길이가 필요한 것이 아닌
    /// 다른 벡터의 단순 길이 비교를 한다면
    /// LengthSqrt() 사용을 권장합니다.
    /// </summary>
    T Length() const;

    /// <summary>
    /// 벡터 크기끼리 길이 비교가 필요할 떄, 주로 사용합니다.
    /// </summary>
    /// <returns></returns>
    constexpr T LengthSq() const;

    /// <summary>
    /// 같은 방향이지만 크기 1로 정규화 합니다.
    ///
    /// *this 는 영 벡터여서는 안됩니다.
    /// </summary>
    /// <returns></returns>
    [[nodiscard]] Vector3 Normalize() const;

    /// <summary>
    /// 두 3 차원 벡터의 내적
    /// </summary>
    constexpr T Dot(const Vector3& rhs) const;

    /// <summary>
    /// 두 3 차원 벡터의 외적
    /// </summary>
    constexpr Vector3<T> Cross(const Vector3& rhs) const;

    /// <summary>
    /// 벡터의 구성성분 끼리 곱(Component-wise multiplication)을 수행합니다.
    ///
    /// 주로 벡터의 스케일링(크기 조절) 작업에서 사용됩니다.
    /// 선형대수학에서 '아르마다 곱' 또는 '슈어 곱'으로 알려져있습니다.
    /// </summary>
    /// <returns>(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z)</returns>
    constexpr Vector3 ComponentWiseMul(const Vector3& rhs) const;

    /// <summary>
    /// 벡터의 구성 성분끼리 나눗셈(Component-wise division)을 수행합니다.
    ///
    /// 주로 벡터의 스케일링(크기 조절) 작업에서 사용됩니다.
    ///
    /// 두 컴포넌트 모두 영벡터여선 안됩니다.
    /// </summary>
    /// <returns>(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z)</returns>
    constexpr Vector3 ComponentWiseDiv(const Vector3& rhs) const;

    void MutiplyAdd(const Vector3& v1, const Vector3& v2, const Vector3& v3);

    Vector3<T> Vector3TransformNormal(const Matrix<T>& matrix) const;
};

/// <summary>
/// Vector3 단항 연산자 - 오버로드
/// </summary>
/// <param name="rhs">뺄 오른쪽 피연산자</param>
/// <returns></returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator-(const Vector3<T>& right);

/// <summary>
///  Vector3 이항 연산자 += 오버로드
///
/// 두 벡터의 맴버별 덧셈을 수행합니다.
/// 그리고 그결과를 왼쪽 값에 할당합니다.
/// </summary>
/// <param name="left">왼쪽 피연산자</param>
/// <param name="right">오른쪽 피연산자</param>
/// <returns>left의 참조</returns>
template <typename T>
constexpr Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right);

/// <summary>
/// Vector3 이항 연산자 -= 오버로드
///
/// 두 벡터의 맴버별 뺄셈을 수행합니다.
/// 그리고 그결과를 왼쪽 값에 할당합니다.
/// </summary>
/// <param name="left">왼쪽 피연산자</param>
/// <param name="right">오른쪽 피연산자</param>
/// <returns>left의 참조</returns>
template <typename T>
constexpr Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right);

/// <summary>
/// Vector3 이항 연산자 + 오버로드
/// </summary>
/// <param name="left">왼쪽 피연산자</param>
/// <param name="right">오른쪽 피연산자</param>
/// <returns>두 벡터의 맴버끼리의 덧셈</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right);

/// <summary>
/// Vector3 이항 연산자 - 오버로드
/// </summary>
/// <param name="left">왼쪽 피연산자</param>
/// <param name="right">오른쪽 피연산자</param>
/// <returns>두 벡터의 맴버끼리의 뺄셈</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right);

/// <summary>
/// Vector3 이항 연산자 * 오버로드
/// </summary>
/// <param name="left">왼쪽 피연산자 (스칼라 값)</param>
/// <param name="right">오른쪽 피연산자 (벡터)</param>
/// <returns>right와의 곱셈</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator*(const Vector3<T>& left, T right);

/// <summary>
/// Vector3 이항 연산자 * 오버로드
/// </summary>
/// <param name="left">왼쪽 피연산자 (벡터)</param>
/// <param name="right">오른쪽 피연산자 (스칼라 값)</param>
/// <returns>left와의 곱셈</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator*(T left, const Vector3<T>& right);

/// <summary>
/// Vector3 이항 연산자 *= 오버로드
///
/// 벡터의 맴버들과 left의 곱셈 수행합니다.
/// 그리고 그결과를 왼쪽 값에 할당합니다.
/// </summary>
/// <param name="left">왼쪽 피연산자 (벡터)</param>
/// <param name="right">오른쪽 피연산자 (스칼라 값)</param>
/// <returns>left의 참조</returns>
template <typename T>
constexpr Vector3<T>& operator*=(Vector3<T>& left, T right);

/// <summary>
/// Vector3 이항 연산자 / 오버로드
/// </summary>
/// <param name="left">왼쪽 피연산자 (벡터)</param>
/// <param name="right">오른쪽 피연산자 (스칼라 값)</param>
/// <returns>left와의 나눗셈</returns>
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator/(const Vector3<T>& left, T right);

/// <summary>
/// Vector3 이항 연산자 /= 오버로드
///
/// 벡터의 맴버들과 left의 나눗셈을 수행합니다.
/// 그리고 그결과를 왼쪽 값에 할당합니다.
/// </summary>
/// <param name="left">왼쪽 피연산자</param>
/// <param name="right">오른쪽 피연산자</param>
/// <returns>left의 참조</returns>
template <typename T>
constexpr Vector3<T>& operator/=(Vector3<T>& left, T right);

/// <summary>
///  Vector3 이항 연산자 == 오버로드
///
/// 두 벡터를 바교합니다.
/// </summary>
/// <param name="left">왼쪽 피연산자</param>
/// <param name="right">오른쪽 피연산자</param>
/// <returns>left 가 right 와 같아면 참</returns>
template <typename T>
[[nodiscard]] constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right);

/// <summary>
///  Vector2 이항 연산자 != 오버로드
///
/// 두 벡터를 바교합니다.
/// </summary>
/// <param name="left">왼쪽 피연산자</param>
/// <param name="right">오른쪽 피연산자</param>
/// <returns>left 가 right 와 다르다면 참</returns>
template <typename T>
[[nodiscard]] constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right);

} // namespace me

#include "Vector3.inl"