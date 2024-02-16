#pragma once

#include <directxmath.h>

namespace graphics
{

class Light
{
public:
    Light();
    Light(const Light&);
    ~Light();

    void SetDiffuseColor(float red, float green, float blue, float alpha);
    void SetDirection(float x, float y, float z);

    DirectX::XMFLOAT4 GetDiffuseColor();
    DirectX::XMFLOAT3 GetDirection();

private:
    DirectX::XMFLOAT4 _diffuseColor;
    DirectX::XMFLOAT3 _direction;
};

} // namespace graphics