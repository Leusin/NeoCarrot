#pragma once
#include <memory>

namespace game
{
class Mouse;
class Keyboard;

class InputManager
{
public:
    InputManager();

private:
    std::unique_ptr<Mouse>    _mouse{nullptr};
    std::unique_ptr<Keyboard> _keybard{nullptr};
};

} // namespace game