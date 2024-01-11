#include "CameraScript.h"

#include "Entity.h"
#include "Camera.h"
#include "Transform.h"
#include "Vector3.h"

#include <windows.h>
#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

CameraScript::CameraScript(EntityPtr entityPtr) 
    : _entity{EntityPtr(entityPtr)}
    , _camera{_entity.lock()->GetComponent<game::Camera>()}
    , _transform{_entity.lock()->GetComponent<game::Transform>()}
{
    assert(_camera && "camera script �� camera ������ �ҷ��� �� ����");
    assert(_transform && "camera script �� _transform ������ �ҷ��� �� ����");

    _transform->SetPosition({0.0f, 2.0f, -15.0f});

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Camera Script Component\n";
#endif // _DEBUG
}

CameraScript::~CameraScript()
{
    _entity.reset();
}

void CameraScript::Update(float dt)
{
    // ī�޶� ����

    float speed = 0.0001f;
    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
        speed = 0.002f;
    else
        speed = 0.0001f;

    if (GetAsyncKeyState('W') & 0x8000)
    {
        _camera->Walk(10.0f * speed);
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        _camera->Walk(-10.0f * speed);
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        _camera->Strafe(-10.0f * speed);
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        _camera->Strafe(10.0f * speed);
    }
}

} // namespace game