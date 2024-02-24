#include "EntityFactory.h"

#include "../UnityLike_Core/Entity.h"
#include "EntityBuilder.h"

namespace game
{

EntityPtr EntityFactory::CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name)
{
    switch (enumTypeEntity)
    {
        case core::GameObect::CAMERA:
            return CreateCamera(std::forward<const size_t>(id), std::move(name));
        default: break;
    }

    return nullptr;
}

EntityPtr EntityFactory::CreateCamera(const size_t&& id, const char* name)
{
    auto builder = EntityBuilder(
        std::forward<const size_t>(id), 
        std::move(name), 
        core::Tag::CAMERA, 
        core::Layer::BACKGROUND);

    auto camera = 
        builder
        .AddTransform()
        .AddCamera()
        .AddCameraScript()
        .Build();

    return camera;
}

} // namespace game