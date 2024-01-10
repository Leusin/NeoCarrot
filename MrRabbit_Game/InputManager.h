#pragma once

#include <memory>
#include "Mouse.h"

namespace game
{
/*
class Mouse;
class Keyboard;
*/

class InputManager
{
public:
    InputManager();

    void Update(float dt);
    // GetKeyState
    // IsKeyState

    // GetMousePosition
    // GetDeltaMousePosition


private:
    //std::unique_ptr<Mouse>    _mouse{nullptr};
    /*
    std::unique_ptr<Keyboard> _keybard{nullptr};
    */
};

} // namespace game