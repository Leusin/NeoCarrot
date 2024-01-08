/// MouseButtonType.h : 마우스의 입력을 정의한 열거 클래스 입니다.
///
/// 2024-01-08

#pragma once

namespace game
{
namespace mouse
{

enum class Button
{
    Left,    // 마우스 왼쪽 버튼
    Right,   // 마우스 오른쪽 버튼
    Middle,  // 마우스 가운데(스크롤 휠) 버튼
    Extra1,  // 첫번째 마우스 추가 버튼
    Extra2,  // 두번째 마우스 추가 버튼

    BUTTON_COUNT
};

enum class Wheel
{
    VERTICAL,   // 수직 마우스 휠
    HORIZONTAL, // 수평 마우스 휠

    WHEEL_COUNT
};

} // namespace mouse
} // namespace game