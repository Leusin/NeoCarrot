#include "CameraScript.h"

#include "Camera.h"
#include "Entity.h"

#include "Camera.h"
#include "Vector3.h"

#include <windows.h>
#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

CameraScript::CameraScript(EntityPtr entityPtr) :
_entity{EntityPtr(entityPtr)},
_camera{_entity.lock()->GetComponent<game::Camera>()}
{
    assert(_camera);

    auto ca = _entity.lock()->GetComponent<game::Camera>();
    _camera->SetPosition(0.0f, 2.0f, -15.0f);
    _camera->LookAt(math::Vector3<float>(10.f, 10.f, 10.f),
                    math::Vector3<float>(0.f, 0.f, 0.f),
                    math::Vector3<float>(0.f, 1.f, 0.f));
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Camera Script Component\n";
#endif // _DEBUG
}

CameraScript::~CameraScript()
{
    _entity.reset();
}

void CameraScript::Start()
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