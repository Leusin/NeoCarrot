#pragma once

#include "IFactory.h"

namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{
class ResourceManager;
class ModelFactory : public core::IFactory
{
public:
    ModelFactory(ResourceManager* _resourceManager);

    EntityPtr CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name);

private:
    EntityPtr CreateAxis(const size_t&& id, const char* name);
    EntityPtr CreateBox(const size_t&& id, const char* name);
    ResourceManager* _resourceManager;
};

} // namespace graphics