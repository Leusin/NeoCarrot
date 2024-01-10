#include "CameraScript.h"

#include "Entity.h"

#include <windows.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

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
#ifdef _DEBUG
         std::cout << 'W' << std::endl;
#endif // _DEBUG
     }
     if (GetAsyncKeyState('S') & 0x8000)
     {
         //_camera->Walk(-10.0f * speed);
#ifdef _DEBUG
         std::cout << 'S' << std::endl;
#endif // _DEBUG
     }
     if (GetAsyncKeyState('A') & 0x8000)
     {
         //_camera->Strafe(-10.0f * speed);
#ifdef _DEBUG
         std::cout << 'A' << std::endl;
#endif // _DEBUG
     }
     if (GetAsyncKeyState('D') & 0x8000)
     {
         //_camera->Strafe(10.0f * speed);
#ifdef _DEBUG
         std::cout << 'D' << std::endl;
#endif // _DEBUG
     }
}

} // namespace game