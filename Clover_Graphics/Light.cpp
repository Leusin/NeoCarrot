#include "Light.h"

namespace graphics
{

Light::Light()
{
}

Light::Light(const Light&)
{
}

Light::~Light()
{
}

void Light::SetDiffuseColor(float r, float g, float b, float a)
{
    _diffuseColor = DirectX::XMFLOAT4(r, g, b, a);
}

void Light::SetDirection(float x, float y, float z)
{
    _direction = DirectX::XMFLOAT3(x, y, z);
}

DirectX::XMFLOAT4 Light::GetDiffuseColor()
{
    return _diffuseColor;
}

DirectX::XMFLOAT3 Light::GetDirection()
{
    return _direction;
}

} // namespace graphics