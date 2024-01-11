#include "ModelFactory.h"

#include "../UnityLike_Core/Entity.h"
#include "ModelBuilder.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
ModelFactory::ModelFactory()
{
#if defined(DEBUG) || defined(_DEBUG)
    std::cout << "\t\tModelFactory Constructed\n";
#endif
}

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