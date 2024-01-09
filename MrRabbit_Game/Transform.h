#pragma once

#include "../UnityLike_Core/IComponent.h"

namespace game
{

class Transform : public core::IComponent
{
public:
    Transform();
    ~Transform();
};

} // namespace game