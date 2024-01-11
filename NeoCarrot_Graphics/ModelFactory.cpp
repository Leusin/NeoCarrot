#include "ModelFactory.h"

#include "../UnityLike_Core/Entity.h"

namespace graphics
{
EntityPtr ModelFactory::CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name)
{
    switch (enumTypeEntity)
    {
        case core::GameObect::BOX:
            //return CreateCamera(std::forward<const size_t>(id), std::move(name));
        default:
            break;
    }

    return nullptr;
}
EntityPtr ModelFactory::CreateBox(const size_t&& id, const char* name)
{
    return EntityPtr();
}
} // namespace graphics