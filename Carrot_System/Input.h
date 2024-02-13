#pragma once

#include <windows.h>

namespace game
{
class IScene;
/*
class Keyboard;
*/

class Input
{
class CameraScript;

public:
    Input(HWND* hMainWnd);
    Input(const Input&);
    ~Input();

    void Initialize();

    void KeyDown(unsigned int input);
    void KeyUp(unsigned int input);
    bool isKeyDown(unsigned int input);

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);


    IScene* _currentscene;
private:
    // Ű����
    bool _keys[256];

    // ���콺
    POINT _lastMousePos;

    HWND* _hMainWnd{nullptr};
};

} // namespace game