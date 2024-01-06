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
    //shared_ptr<Object<Type, Layer>> entity = 
    //    make_shared<Object<Type, Layer>>(0, "me", Type::HERO, Layer::ZERO);

    //obj->Destroy();

	return 0;
}