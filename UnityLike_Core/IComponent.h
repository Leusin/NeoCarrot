/// IComponent.h
///
/// 구현할만한 Component 속성
///
///    - Transform
///    - Renderor
///    - Collider
///    - Script
///    - Prefab
///    - Hierachy
///    - Active/Inactive
///
/// 2024-01-06


#pragma once

#include "IEventFunction.h"

#include <memory>

namespace core
{

class IComponent : public IEventFunction
{
public:
    IComponent();
    virtual ~IComponent();
};

} // namespace core