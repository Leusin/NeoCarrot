#include "Transpose_mk2.h"

#include "Camera3D.h"

#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
Transpose_mk2::Transpose_mk2(Camera3D* camera)
    : _camera(camera)
    , _world{}
    , _view{}
    , _proj{}
    , _eyePosW{}
{
    DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();
    XMStoreFloat4x4(&_world, I);
    XMStoreFloat4x4(&_view, I);
    XMStoreFloat4x4(&_proj, I);
    assert(camera && "Transpose_mk2 에서 Camera3D 를 찾을 수 없음");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd CameraPtr Component\n";
#endif // _DEBUG
}

void Transpose_mk2::Update(float dt)
{
    UpdateDataFormCamera();
}

//////////////////////////////////////////////////////////////////////
DirectX::XMMATRIX Transpose_mk2::GetWorld()
{
    return DirectX::XMLoadFloat4x4(&_world);
}

DirectX::XMMATRIX Transpose_mk2::GetView()
{
    return DirectX::XMLoadFloat4x4(&_view);
}

DirectX::XMMATRIX Transpose_mk2::GetProj()
{
    return DirectX::XMLoadFloat4x4(&_proj);
}

DirectX::XMMATRIX Transpose_mk2::GetWorldViewProj()
{
    return GetWorld() * GetView() * GetProj();
}

void Transpose_mk2::SetWorld(const DirectX::XMMATRIX& world)
{
    DirectX::XMStoreFloat4x4(&_world, world);
}

void Transpose_mk2::SetView(const DirectX::XMMATRIX& view)
{
    DirectX::XMStoreFloat4x4(&_view, view);
}

void Transpose_mk2::SetProj(const DirectX::XMMATRIX& proj)
{
    DirectX::XMStoreFloat4x4(&_proj, proj);
}

void Transpose_mk2::SetTM(const DirectX::XMMATRIX& world,
                          const DirectX::XMMATRIX& view,
                          const DirectX::XMMATRIX& proj)
{
    DirectX::XMStoreFloat4x4(&_world, world);
    DirectX::XMStoreFloat4x4(&_view, view);
    DirectX::XMStoreFloat4x4(&_proj, proj);
}

//////////////////////////////////////////////////////////////////////
void Transpose_mk2::UpdateDataFormCamera()
{
    auto world = GetWorld();
    auto view  = _camera->View();
    auto proj  = _camera->Proj();
    SetTM(world, view, proj);
    _eyePosW = _camera->GetPosition();
}

} // namespace graphics