#include "Camera.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{
Camera::Camera()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Camera Component\n";
#endif // _DEBUG
}
Camera::~Camera()
{
}
} // namespace game