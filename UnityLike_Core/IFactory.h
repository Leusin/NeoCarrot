/// 2024-01-11

#pragma once

#include "EntityEnum.h"

#include <memory>
#include <vector>

namespace core
{
template<typename T, typename U>
class Entity;

using EntityPtr = std::shared_ptr<core::Entity<Tag, Layer>>;

class IFactory
{

public:
    IFactory()          = default;
    virtual ~IFactory() = default;

    virtual EntityPtr CreateEntity(core::GameObect enumTypeEntity,
                                   const size_t&& id,
                                   const char* name) abstract;
};

} // namespace core