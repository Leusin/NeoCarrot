#include "EntityFactory.h"

#include "../UnityLike_Core/Entity.h"
#include "EntityBuilder.h"

namespace game
{

EntityPtr EntityFactory::CreateEntity(game::Entity enumTypeEntity,const size_t&& id, const char* name)
{
    switch (enumTypeEntity)
    {
        case game::Entity::CAMERA:
            return CreateCarEntity(std::forward<const size_t>(id), std::move(name));
        default: break;
    }

    return nullptr;
}

EntityPtr EntityFactory::CreateCarEntity(const size_t&& id, const char* name)
{
    auto builder = EntityBuilder(
        std::forward<const size_t>(id), 
        std::move(name), 
        Tag::CAMERA, 
        Layer::BACKGROUND);

    auto camera = 
        builder
        .AddTransform()
        .AddCamera()
        .AddCameraScript()
        .Build();

    return camera;
}

} // namespace game