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
    assert(!cameras.empty() && "카메라 개체가 반드시 하나 이상 있어야함");
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
    assert(!_cameras.empty() && "카메라 개체가 반드시 하나 이상 있어야함");

     for (auto& e : _cameras)
    {
        auto camera = e.lock();

        if (camera->_isActive)
        {
            return camera;
        }
    }

     assert(false && "활성된 카메라가 없음");

    return WeakEntityPtr();
}

}