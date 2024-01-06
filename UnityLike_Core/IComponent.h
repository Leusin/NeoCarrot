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

#ifdef CORE_Test
#include <iostream>
#endif // CORE_Test

IComponent::IComponent()
{
    // TEST
#ifdef CORE_Test
    printf("\t\tIComponent Constructed\n");
#endif // CORE_Test
}

IComponent::~IComponent()
{
    // TEST
#ifdef CORE_Test
    printf("\t\tIComponent Distructed\n");
#endif // CORE_Test
}

} // namespace core