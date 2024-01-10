/// MouseButtonType.h : ���콺�� �Է��� ������ ���� Ŭ���� �Դϴ�.
///
/// 2024-01-08

#pragma once

namespace game
{
namespace mouse
{

enum class Button
{
    LEFT,    // ���콺 ���� ��ư
    RIGHT,   // ���콺 ������ ��ư
    MIDDLE,  // ���콺 ���(��ũ�� ��) ��ư
    EXTRA1,  // ù��° ���콺 �߰� ��ư
    EXTRA2,  // �ι�° ���콺 �߰� ��ư

    BUTTON_COUNT
};

enum class Wheel
{
    VERTICAL,   // ���� ���콺 ��
    HORIZONTAL, // ���� ���콺 ��

    WHEEL_COUNT
};

} // namespace mouse
} // namespace game