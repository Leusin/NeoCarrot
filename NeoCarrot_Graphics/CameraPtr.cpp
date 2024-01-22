#include "CameraPtr.h"

#include "Camera3D.h"
#include "Entity.h"
#include "Transpose.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
CameraPtr::CameraPtr(EntityPtr entityPtr, Camera3D* camera) 
    : GetEntity(EntityPtr(entityPtr))
    , _transpose(GetComponent<graphics::Transpose>())
    , _camera(camera)
{
    assert(_transpose && "CameraPtr ���� Transpose �� ã�� �� ����");
    assert(_transpose && "CameraPtr ���� Camera3D �� ã�� �� ����");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd CameraPtr Component\n";
#endif // _DEBUG
}

void CameraPtr::Update(float dt)
{
    auto world = _transpose->GetWorld();
    auto view = _camera->View();
    auto proj = _camera->Proj();
    _transpose->SetTM(world, view, proj);
    
    _transpose->_eyePosW = _camera->GetPosition();
}

} // namespace graphics