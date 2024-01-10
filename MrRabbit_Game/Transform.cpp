#include "Transform.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{
Transform::Transform()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Transform Component\n";
#endif // _DEBUG
}

Transform::~Transform()
{
}
} // namespace game