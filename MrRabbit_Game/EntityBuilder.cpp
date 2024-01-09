#include "EntityBuilder.h"

#include "../UnityLike_Core/Entity.h"
#include "Transform.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

EntityBuilder::EntityBuilder(const size_t&& id, const char* name, Tag&& tag, Layer&& layer) :
_entity(
    std::make_shared<core::Entity<Tag, Layer>>(std::forward<const size_t>(id), std::move(name), std::move(tag), std::move(layer)))
{
#ifdef _DEBUG
    std::cout << "\t\tCreate Entity ( " << name << ", " << static_cast<int>(id)
              << " ) \n";
#endif // _DEBUG
}

EntityBuilder game::EntityBuilder::AddTransform()
{
#ifdef _DEBUG
    std::cout << "\t\t\tAdd Transform Component\n";
#endif // _DEBUG
    
    _entity->AddComponent<Transform>();

    return *this;
}

EntityPtr EntityBuilder::Build()
{
    return _entity;
}

}