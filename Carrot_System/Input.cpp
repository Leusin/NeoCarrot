#include "Input.h"

namespace game
{

Input::Input(HWND* hMainWnd)
    : _hMainWnd{ hMainWnd }
    , _keys{}
    , _lastMousePos{}
{
}

Input::Input(const Input&)
{
}

Input::~Input()
{
}

void Input::Initialize()
{
}

void Input::KeyDown(unsigned int input)
{
    _keys[input] = true;
}

void Input::KeyUp(unsigned int input)
{
    _keys[input] = false;
}

bool Input::isKeyDown(unsigned int input)
{
    return _keys[input];
}

void Input::OnMouseDown(WPARAM btnState, int x, int y)
{
    _lastMousePos = POINT{ x, y };
    SetCapture(*_hMainWnd);
}

void Input::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void Input::OnMouseMove(WPARAM btnState, int x, int y)
{
}

} // namespace game
