#include "InputManager.h"

#include "Entity.h"
#include "EntityEnum.h"

#include "IScene.h"
#include "Camera.h"
#include "CameraScript.h"
#include "CameraManager.h"

//#include <WinUser.h>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <DirectXMath.h>

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


InputManager::InputManager(HWND* hMainWnd) 
: _hMainWnd{hMainWnd}
{
#ifdef _DEBUG
    std::cout << "\tInputManager Constructed\n";
#endif // _DEBUG
}

void InputManager::OnMouseDown(WPARAM btnState, int x, int y)
{
    _lastMousePos = POINT{x, y};

    SetCapture(*_hMainWnd);
}

void InputManager::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}


/// 
/// TODO
///    Pitch, RotateY 따로 호출하면 괜찮은데
///    같이 호출하면 z 축이 회전한다.
///    따라서 언젠간 고칠것
/// 
/// 2024-01-17
void InputManager::OnMouseMove(WPARAM btnState, int x, int y)
{
    if ((btnState & MK_LBUTTON) != 0)
    {
        // 픽셀 하나가 사분의 일(0.25) 도에 해당하도록 만듦
        float dx = DirectX::XMConvertToRadians(0.25f * static_cast<float>(x - _lastMousePos.x));
        float dy = DirectX::XMConvertToRadians(0.25f * static_cast<float>(y - _lastMousePos.y));

        auto* cameraManager       = _currentscene->_cameraManager.get();
        auto weackCamera = cameraManager->GetActiveCamera();

        if (!weackCamera.expired())
        {
            auto* camera = weackCamera.lock()->GetComponent<Camera>();
            //camera->Pitch(dy);
            camera->RotateY(dx);
        }
    }
    _lastMousePos = POINT{x, y};
}

} // namespace game
