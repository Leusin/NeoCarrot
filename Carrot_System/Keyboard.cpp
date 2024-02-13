#include "Keyboard.h"

#include <WinUser.h>

namespace game
{

bool game::Keyboard::IsKeyPressed(keyboard::Key key)
{
    if ((static_cast<int>(key) < 0) || (static_cast<int>(key) >= static_cast<int>(_keyMap.size())))
        return false;

    //update(); ??? ³Ê¹¹³Ä
    return _keyMap[key];

    return false;
}

bool game::Keyboard::IsKeyDown() const
{
    return _isKeyDown;
}

bool game::Keyboard::IsKeyUp() const
{
    return _isKeyUp;
}

bool game::Keyboard::DownAlt()
{
    return _keyMap[keyboard::Key::LAlt] || _keyMap[keyboard::Key::RAlt];
}

bool game::Keyboard::DownControl()
{
    return _keyMap[keyboard::Key::LControl] || _keyMap[keyboard::Key::RControl];
}

bool game::Keyboard::DownShift()
{
    return _keyMap[keyboard::Key::LShift] || _keyMap[keyboard::Key::RShift];
}

bool game::Keyboard::DownSystem()
{
    return _keyMap[keyboard::Key::LSystem] || _keyMap[keyboard::Key::RSystem];
}

std::optional<keyboard::Key> game::Keyboard::CheckKeys()
{
    // clang-format off
    if (GetAsyncKeyState('Q')) return keyboard::Key::Q;
    if (GetAsyncKeyState('W')) return keyboard::Key::W;
    if (GetAsyncKeyState('E')) return keyboard::Key::E;
    if (GetAsyncKeyState('R')) return keyboard::Key::R;

    if (GetAsyncKeyState('A')) return keyboard::Key::A;
    if (GetAsyncKeyState('S')) return keyboard::Key::S;
    if (GetAsyncKeyState('D')) return keyboard::Key::D;
    if (GetAsyncKeyState('F')) return keyboard::Key::F;
    // clang-format on

    return keyboard::Key::Unknown;
}

void game::Keyboard::Process(float dt)
{
    auto pressedKey = CheckKeys();

    if (pressedKey.has_value())
    {
        if (!_keyMap[pressedKey.value()])
        {
            _isKeyDown = true;
            _isKeyUp   = false;
        }
        _keyMap[pressedKey.value()] = true;
    }
    else
    {
        if (!_isKeyUp)
        {
            _isKeyDown = false;
            _isKeyUp   = true;
        }
    }
}

} // namespace game