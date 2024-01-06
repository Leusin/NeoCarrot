#include "Entity.h"

#include <memory>

using namespace std;
using namespace core;

enum class Type
{
    HERO,
    ENEMY
};

enum class Layer
{
    ZERO,
    ONE
};

enum class Component
{
    TRANSFORM
};

int main()
{
    /*shared_ptr<Entity<Type, Layer, Component>>
        entity = make_shared<Entity<Type, Layer, Component>>(0, "me", Type::HERO, Layer::ZERO);

    entity->Destroy();*/

    return 0;
}