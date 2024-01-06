#define CORE_Test

#include "Entity.h"
#include "IComponent.h"

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


class TestComponent1 : public IComponent
{
public:
    int a = 0;
};

class TestComponent2 : public IComponent
{
public:
    TestComponent2(int n) : a(n){}

    int a = 0;
};

class TestComponent3 : public IComponent
{
public:
    TestComponent3(char n) : a(n)
    {
    }

    char a;
};

int main()
{
    shared_ptr<Entity<Type, Layer>>
        entity = make_shared<Entity<Type, Layer>>(0, "me", Type::HERO, Layer::ZERO);

    entity->AddComponent<TestComponent1>();
    entity->AddComponent<TestComponent2>(1);
    entity->AddComponent<TestComponent3>('a');

    entity->Destroy();

    return 0;
}

#undef CORE_Test