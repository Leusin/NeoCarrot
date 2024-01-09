/// IComponent.h
///
/// �����Ҹ��� Component �Ӽ�
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