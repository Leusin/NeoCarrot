#include "Mouse.h"

#include <WinUser.h>
#include <windef.h>

namespace game
{

bool Mouse::IsButtonPressed(mouse::Button button) const
{
    if ((static_cast<int>(button) < 0) ||
        (static_cast<int>(button) >= static_cast<unsigned int>(mouse::Button::BUTTON_COUNT)))
        return false;

    return _mouseMap[button];
}

me::Vector2<int> Mouse::GetPosition()
{
    GetCursorPos(&_mousePos);
    return _mousePos;
}

bool Mouse::IsMouseDown() const
{
    return _isMouseDown;
}

bool Mouse::IsMouseUp() const
{
    return _isMouseUp;
}

std::optional<mouse::Button> Mouse::CheckButton() const
{

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        return mouse::Button::Left;
    else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
        return mouse::Button::Right;
    else if (GetAsyncKeyState(VK_MBUTTON) & 0x8000)
        return mouse::Button::Middle;
    else if (GetAsyncKeyState(VK_XBUTTON1) & 0x8000)
        return mouse::Button::Extra1;
    else if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000)
        return mouse::Button::Extra2;

    return std::nullopt;
}

void Mouse::Process(float dt)
{
    auto pressedButton = CheckButton();

    if (pressedButton.has_value())
    {
        if (!_mouseMap[pressedButton.value()])
        {
            _isMouseDown = true;
            _isMouseUp   = false;
        }
        _mouseMap[pressedButton.value()] = true;
    }
    else
    {
        if (!_isMouseUp)
        {
            _isMouseDown = false;
            _isMouseUp   = true;
        }
    }
}

} // namespace game