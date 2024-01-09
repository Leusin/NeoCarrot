#include "IComponent.h"

namespace core
{
#ifdef CORE_Test
#include <iostream>
#endif // CORE_Test

IComponent::IComponent()
{
    // TEST
#ifdef CORE_Test
    printf("\t\tIComponent Constructed\n");
#endif // CORE_Test
}

IComponent::~IComponent()
{
    // TEST
#ifdef CORE_Test
    printf("\t\tIComponent Distructed\n");
#endif // CORE_Test
}

} // namespace core