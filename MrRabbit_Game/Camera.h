/// Camera.h : 엔티티가 컴포넌트로서 가질 수 있는 카메라.
/// directxmath 에 의존하지 않고 따로 만든 수학 라이브러리를 사용한다.
///
/// 2024-01-09

#pragma once

#include "../UnityLike_Core/IComponent.h"
#include "../Bunny_Math/Vector3.h"

namespace game
{

class Camera : public core::IComponent
{
public:
    Camera();
    ~Camera();

private:
    // 월드 기준 카메라 좌표계
    // 원점
    me::Vector3<float> _position{0.0f, 0.0f, 0.0f};
    // 기저
    me::Vector3<float> _right{1.0f, 0.0f, 0.0f}; // x
    me::Vector3<float> _up{0.0f, 1.0f, 0.0f};    // y
    me::Vector3<float> _look{0.0f, 0.0f, 1.0f};  // z

    // 절두체 속성
    float _nearZ;
    float _farZ;
    float _aspect; // 종횡비
    float _fovY;   // y 시야각
    float _nearWindowHeight;
    float _farWindowHeight;

    /// TODO 
    ///   4x4 행렬을 만든 뒤
    ///   아래 맴버 추가
    // 시야행렬 및 투영 행렬
    // DirectX::XMFLOAT4X4 _view;
    // DirectX::XMFLOAT4X4 _proj;
};

} // namespace game