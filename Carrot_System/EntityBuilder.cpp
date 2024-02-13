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

EntityBuilder::EntityBuilder(const size_t&& id, const char* name, core::Tag&& tag, core::Layer&& layer) :
_entity(std::make_shared<core::Entity<core::Tag, core::Layer>>(std::forward<const size_t>(id),
                                                            std::move(name),
                                                            std::move(tag),
                                                            std::move(layer)))
{
#ifdef _DEBUG
    std::cout << "\t\t\tCreate Game Entity ( " << name << ", " << static_cast<int>(id)
              << " ) \n";
#endif // _DEBUG
}

EntityBuilder game::EntityBuilder::AddTransform()
{   
    _entity->AddComponent<Transform>();

    return *this;
}

EntityBuilder EntityBuilder::AddCamera()
{
    _entity->AddComponent<Camera>(_entity);

    return *this;
}

EntityBuilder EntityBuilder::AddCameraScript()
{
    _entity->AddComponent<CameraScript>(_entity);

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