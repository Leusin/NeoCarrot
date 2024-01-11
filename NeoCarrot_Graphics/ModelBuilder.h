#pragma once

#include "EntityEnum.h"

#include <memory>

namespace core
{
template <typename T, typename U>
class Entity;
} // namespace core

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{

class ModelBuilder
{
public:
    ModelBuilder(const size_t&& id, const char* name, core::Tag&& tag, core::Layer&& layer);

    // ��ǰ ��ȯ
    EntityPtr Build();

private:

    EntityPtr _entity;
};

}