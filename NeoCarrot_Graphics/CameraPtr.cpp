#include "CameraPtr.h"

#include "Camera3D.h"
#include "Entity.h"
#include "Transpose.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
CameraPtr::CameraPtr(EntityPtr entityPtr, Camera3D* camera) :
_entity{EntityPtr(entityPtr)},
_transpose(_entity.lock()->GetComponent<graphics::Transpose>()),
_camera(camera)
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd CameraPtr Component\n";
#endif // _DEBUG
}

void CameraPtr::Update(float dt)
{

#ifdef _DEBUG
    std::cout << "\t\t\t\t\tCameraPtr Update\n";
#endif // _DEBUG


    auto view = _camera->View();
    auto proj = _camera->Proj();
    auto eye  = _camera->GetPosition();
    
    _transpose->SetTM(DirectX::XMMatrixIdentity(), view, proj);
    _transpose->_eyePosW = eye;
}

} // namespace graphics