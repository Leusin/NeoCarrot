#include "EntityBuilder.h"

#include "../UnityLike_Core/Entity.h"
#include "Transform.h"
#include "Camera.h"

#include "CameraScript.h"

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
    std::cout << "\t\t\tCreate Entity ( " << name << ", " << static_cast<int>(id)
              << " ) \n";
#endif // _DEBUG
}

EntityBuilder game::EntityBuilder::AddTransform()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Transform Component\n";
#endif // _DEBUG
    
    _entity->AddComponent<Transform>();

    return *this;
}

EntityBuilder EntityBuilder::AddCamera()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Camera Component\n";
#endif // _DEBUG

    _entity->AddComponent<Camera>();

    return *this;
}

EntityBuilder EntityBuilder::AddCameraScript()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd CameraScript Component\n";
#endif // _DEBUG

    _entity->AddComponent<CameraScript>();

    return *this;
}

EntityPtr EntityBuilder::Build()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tEnd build\n";
#endif // _DEBUG

    return _entity;
}

}