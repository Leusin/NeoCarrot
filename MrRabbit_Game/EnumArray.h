/// InputEnumArray.h : 특정 열거형을 키로 사용하고, 그에 따른 값을 저장하는
/// 고정된 크기 배열(Fixed-size array) 을 정의한 구조체 입니다.
/// 
/// 마우스, 키보드 같은 입출력 시스템에서 사용됩니다.
///
/// 2024-01-08

#pragma once

#include <array>
#include <type_traits>

#include <cassert>
#include <cstddef>

namespace game
{

/// <summary>
/// 특정 열거형을 키로 사용하며 그에 따른 값을 저장하는 고정 크기 배열입니다.
/// std::array을 상속 받기 때문에 std::array의 모든 기능을 그대로 상속받습니다.
/// </summary>
/// <typeparam name="Enum">열거형</typeparam>
/// <typeparam name="Value">저장할 값의 타입</typeparam>
/// <typeparam name="Count">열거형 배열의 크기</typeparam>
template <typename Enum, typename Value, std::size_t Count>
struct EnumArray : public std::array<Value, Count>
{
    static_assert(std::is_enum_v<Enum>, "Enum 타입 파라미터는 반드시 열거형이야 합니다.\nEnum type parameter must be an enumeration");

    /// <summary>
    /// 
    /// </summary>
    /// <param name="key">열거형의 요소</param>
    /// <returns>키와 관련된 값 배열을 반환합니다.</returns>
    constexpr Value& operator[](Enum key)
    {
        const auto index = static_cast<std::size_t>(key);
        assert(index < Count && "인덱스가 범위를 벗어납니다.\nIndex is out of bounds");
        return std::array<Value, Count>::operator[](index);
    }

    /// <summary>
    /// 열거형 맴버를 통해 자료를 접근하여 
    /// </summary>
    /// <param name="key">열거형의 요소</param>
    /// <returns>키와 관련된 값 배열을 반환합니다.</returns>
    constexpr const Value& operator[](Enum key) const
    {
        const auto index = static_cast<std::size_t>(key);
        assert(index < Count && "인덱스가 범위를 벗어납니다.\nIndex is out of bounds");
        return std::array<Value, Count>::operator[](index);
    }
};

} // namespace game