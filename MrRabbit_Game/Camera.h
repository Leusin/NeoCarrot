/// Camera.h : 엔티티가 컴포넌트로서 가질 수 있는 카메라.
/// directxmath 에 의존하지 않고 따로 만든 수학 라이브러리를 사용한다.
///
/// 2024-01-09

#pragma once

#include "../UnityLike_Core/IComponent.h"


namespace game
{

class Camera : public core::IComponent
{
public:
    Camera();
    ~Camera();
};

} // namespace game