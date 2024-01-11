#include "ModelFactory.h"

#include "../UnityLike_Core/Entity.h"
#include "ModelBuilder.h"

namespace graphics
{
EntityPtr ModelFactory::CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name)
{
    switch (enumTypeEntity)
    {
        case core::GameObect::BOX:
            return CreateBox(std::forward<const size_t>(id), std::move(name));
        default:
            break;
    }

    return nullptr;
}
EntityPtr ModelFactory::CreateBox(const size_t&& id, const char* name)
{
    /*
    * auto builder = EntityBuilder(
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
    */

    auto builder = ModelBuilder(
        std::forward<const size_t>(id), 
        std::move(name), 
        core::Tag::MESHOBJ, 
        core::Layer::FORGROUND);

    auto box = 
        builder
        .Build();

    return box;
}
} // namespace graphics