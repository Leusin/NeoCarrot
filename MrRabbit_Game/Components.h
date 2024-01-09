#pragma once
#include "../UnityLike_Core/IComponent.h"

namespace game
{

class TestComponent1 : public core::IComponent
{
public:
    int a = 0;
};

class TestComponent2 : public core::IComponent
{
public:
    TestComponent2(int n) : a(n)
    {
    }

    int a = 0;
};

class TestComponent3 : public core::IComponent
{
public:
    TestComponent3(char n) : a(n)
    {
    }

    char a;
};

}