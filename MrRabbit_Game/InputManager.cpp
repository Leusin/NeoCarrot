#include "InputManager.h"

/*
#include "Keyboard.h"
*/

//#include <WinUser.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

enum class InputEvent
{
    KeyPressed,          //!< A key was pressed (data in event.key)
    KeyReleased,         //!< A key was released (data in event.key)
    MouseWheelScrolled,  //!< The mouse wheel was scrolled (data in event.mouseWheelScroll)
    MouseButtonPressed,  //!< A mouse button was pressed (data in event.mouseButton)
    MouseButtonReleased, //!< A mouse button was released (data in event.mouseButton)
    MouseMoved,          //!< The mouse cursor moved (data in event.mouseMove)
    MouseEntered,        //!< The mouse cursor entered the area of the window (no data)
    MouseLeft,           //!< The mouse cursor left the area of the window (no data)
};


InputManager::InputManager() /*: _mouse{std::make_unique<Mouse>()}, _keybard{std::make_unique<Keyboard>()}*/
{
#ifdef _DEBUG
    std::cout << "\tInputManager Constructed\n";
#endif // _DEBUG
}

void InputManager::Update(float dt)
{
    //_mouse->Update(dt);
}

} // namespace game
