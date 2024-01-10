#pragma once
namespace game
{

struct CameraInfo
{
    float _nearZ{000.1f};
    float _farZ{1000.f};
    float _fovY{0.25f};
    float _nearWindowHeight;
    float _farWindowHeight;
};

 }