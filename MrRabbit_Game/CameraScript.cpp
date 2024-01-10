#include "CameraScript.h"

#include "Entity.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <windows.h>

namespace game
{

CameraScript::CameraScript(/*EntityPtr entityPtr*/) 
    /*: _entity(EntityPtr(entityPtr))*/
{
}

CameraScript::~CameraScript()
{
}

void CameraScript::Update(float dt)
{
    // 카메라 제어

     float speed = 0.0001f;
     if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
         speed = 0.002f;
     else
         speed = 0.0001f;
 
     if (GetAsyncKeyState('W') & 0x8000)
     {
         //_camera->Walk(10.0f * speed);
     }
     if (GetAsyncKeyState('S') & 0x8000)
     {
         //_camera->Walk(-10.0f * speed);
     }
     if (GetAsyncKeyState('A') & 0x8000)
     {
         //_camera->Strafe(-10.0f * speed);
     }
     if (GetAsyncKeyState('D') & 0x8000)
     {
         //_camera->Strafe(10.0f * speed);
     }
}

} // namespace game