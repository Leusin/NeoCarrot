#pragma once

#include "EntityEnum.h"
#include <windows.h>

namespace game
{
class IScene;
/*
class Keyboard;
*/

class InputManager
{
class CameraScript;

public:
    InputManager(HWND* hMainWnd);

    //void Update(float dt);

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);


    IScene* _currentscene;
private:

    // ¸¶¿ì½º
    POINT _lastMousePos;
    HWND* _hMainWnd;
};

} // namespace game