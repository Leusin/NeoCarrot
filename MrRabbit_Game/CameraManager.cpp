#include "CameraManager.h"

#include "Entity.h"
#include "Camera.h"
#include "ForGraphics.h"

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

CameraManager::CameraManager()
{

#ifdef _DEBUG
    std::cout << "\t\tCameraManager Constructed\n";
#endif // _DEBUG
}

CameraManager::~CameraManager()
{
}
void CameraManager::GetCameraEntitys(std::vector<WeakEntityPtr> cameras)
{
    assert(!cameras.empty() && "ī�޶� ��ü�� �ݵ�� �ϳ� �̻� �־����");
    _cameras = cameras;
}
void CameraManager::GetActiveCameraInfo(data::ForGraphics* info)
{
    auto getCamera    = GetActiveCamera();
    auto activeCamera = getCamera.lock();

    auto componentCamera = activeCamera->GetComponent<Camera>();

    auto cameraInfo = componentCamera->GetCameraInfo();

    info->_camera = cameraInfo;
}

WeakEntityPtr CameraManager::GetActiveCamera()
{
    assert(!_cameras.empty() && "ī�޶� ��ü�� �ݵ�� �ϳ� �̻� �־����");

     for (auto& e : _cameras)
    {
        auto camera = e.lock();

        if (camera->_isActive)
        {
            return camera;
        }
    }

     assert(false && "Ȱ���� ī�޶� ����");

    return WeakEntityPtr();
}

}