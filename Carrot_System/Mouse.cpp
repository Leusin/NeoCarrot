#include "Mouse.h"

#include <WinUser.h>
#include <windef.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

using mouseMap = game::EnumArray<mouse::Button, bool, static_cast<unsigned int>(mouse::Button::BUTTON_COUNT)>;

math::Vector2<int> _pos{ 0, 0 };
math::Vector2<int> _lastPos{0, 0};

mouseMap _mouseMap;

//////////////////////////////////////////////////////////////////////
void Mouse::Update(float dt)
{
    auto pressedButton = CheckButton();
    auto isPressed     = pressedButton.has_value();
#ifdef _DEBUG
    if (isPressed)
        std::cout << "Mouse Button Pressed" /*<< pressedButton.value()*/ << std::endl;
#endif // _DEBUG

    if (isPressed)
    {
        if (!_mouseMap[pressedButton.value()])
        {
            //_isMouseDown = true;
            //_isMouseUp   = false;
        }
        _mouseMap[pressedButton.value()] = true;
    }
    else
    {
        //if (!_isMouseUp)
        //{
        //    _isMouseDown = false;
        //    _isMouseUp   = true;
        //}
    }
} 

std::optional<mouse::Button> Mouse::CheckButton() const
{
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        return mouse::Button::LEFT;
    else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
        return mouse::Button::RIGHT;
    else if (GetAsyncKeyState(VK_MBUTTON) & 0x8000)
        return mouse::Button::MIDDLE;
    else if (GetAsyncKeyState(VK_XBUTTON1) & 0x8000)
        return mouse::Button::EXTRA1;
    else if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000)
        return mouse::Button::EXTRA2;

    return std::nullopt;
}

} // namespace game

/*
math::Vector2<int> Mouse::GetPosition() 
{
    GetCursorPos(&_pos);
    return _pos;
}
*/

/*
bool Mouse::IsButtonPressed(mouse::Button button) const
{
    if ((static_cast<int>(button) < 0) ||
        (static_cast<int>(button) >= static_cast<unsigned int>(mouse::Button::BUTTON_COUNT)))
        return false;

    return _mouseMap[button];
}

*/