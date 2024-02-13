/// InputEnumArray.h : Ư�� �������� Ű�� ����ϰ�, �׿� ���� ���� �����ϴ�
/// ������ ũ�� �迭(Fixed-size array) �� ������ ����ü �Դϴ�.
/// 
/// ���콺, Ű���� ���� ����� �ý��ۿ��� ���˴ϴ�.
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
/// Ư�� �������� Ű�� ����ϸ� �׿� ���� ���� �����ϴ� ���� ũ�� �迭�Դϴ�.
/// std::array�� ��� �ޱ� ������ std::array�� ��� ����� �״�� ��ӹ޽��ϴ�.
/// </summary>
/// <typeparam name="Enum">������</typeparam>
/// <typeparam name="Value">������ ���� Ÿ��</typeparam>
/// <typeparam name="Count">������ �迭�� ũ��</typeparam>
template <typename Enum, typename Value, std::size_t Count>
struct EnumArray : public std::array<Value, Count>
{
    static_assert(std::is_enum_v<Enum>, "Enum Ÿ�� �Ķ���ʹ� �ݵ�� �������̾� �մϴ�.\nEnum type parameter must be an enumeration");

    /// <summary>
    /// 
    /// </summary>
    /// <param name="key">�������� ���</param>
    /// <returns>Ű�� ���õ� �� �迭�� ��ȯ�մϴ�.</returns>
    constexpr Value& operator[](Enum key)
    {
        const auto index = static_cast<std::size_t>(key);
        assert(index < Count && "�ε����� ������ ����ϴ�.\nIndex is out of bounds");
        return std::array<Value, Count>::operator[](index);
    }

    /// <summary>
    /// ������ �ɹ��� ���� �ڷḦ �����Ͽ� 
    /// </summary>
    /// <param name="key">�������� ���</param>
    /// <returns>Ű�� ���õ� �� �迭�� ��ȯ�մϴ�.</returns>
    constexpr const Value& operator[](Enum key) const
    {
        const auto index = static_cast<std::size_t>(key);
        assert(index < Count && "�ε����� ������ ����ϴ�.\nIndex is out of bounds");
        return std::array<Value, Count>::operator[](index);
    }
};

} // namespace game