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
    Left,    // ���콺 ���� ��ư
    Right,   // ���콺 ������ ��ư
    Middle,  // ���콺 ���(��ũ�� ��) ��ư
    Extra1,  // ù��° ���콺 �߰� ��ư
    Extra2,  // �ι�° ���콺 �߰� ��ư

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