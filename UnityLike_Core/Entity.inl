#pragma once

#ifdef _DEBUG
#include <iostream>
#include "Entity.h"
#endif // DEBUG

namespace core
{
template <typename Tag, typename Layer, typename Component>
inline Entity<Tag, Layer, Component>::Entity(int&& id, const char* name, Tag&& tag, Layer&& layer) :
Object<Tag, Layer>(id, name, std::forward<Tag>(tag), std::forward<Layer>(layer))
{
    // TEST
#ifdef _DEBUG
    printf("\tEntity Construct\n");
#endif // DEBUG
}
template <typename Tag, typename Layer, typename Component>
inline core::Entity<Tag, Layer, Component>::~Entity()
{
    // TEST
#ifdef _DEBUG
    printf("\tEntity Distory\n");
#endif // DEBUG
}
} // namespace core