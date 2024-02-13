/// IScene.h : Scene �� �ϰ����� ȣ�⿡ ���� ������ ������ ���� ������ �������̽� Ŭ�����Դϴ�.
///
/// 2023-12-26

#pragma once

#include "ForGraphics.h"
#include "CameraManager.h"

#include <memory>

namespace data
{
struct ForGraphics;
}

namespace game
{
class IScene
{
public:
    virtual ~IScene(){};

public:
    virtual void Initialize() abstract;
    virtual void Update(float deltaTime) abstract;
    virtual void Finalize() abstract;

    virtual void ExportData(data::ForGraphics* graphicsInfo) abstract;

    std::unique_ptr<CameraManager>  _cameraManager{std::make_unique<CameraManager>()};
public:
    virtual std::shared_ptr<IScene> NextSene() abstract;
};

} // namespace game