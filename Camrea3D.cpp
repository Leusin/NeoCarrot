#include "Camrea3D.h"
#include "../Bunny_Math/Constants.h"

using namespace DirectX;

ge::Camrea3D::Camrea3D()
{
    SetLens(0.25f * me::Constant::PI, 1.0f, 000.1f, 1000.f);
}

ge::Camrea3D::~Camrea3D()
{
}

DirectX::XMVECTOR ge::Camrea3D::GetPositionXM() const
{
    return XMLoadFloat3(&_position);
}

DirectX::XMFLOAT3 ge::Camrea3D::GetPosition() const
{
    return _position;
}

void ge::Camrea3D::SetPosition(float x, float y, float z)
{
    _position = XMFLOAT3(x, y, z);
}

void ge::Camrea3D::SetPosition(const DirectX::XMFLOAT3 &v)
{
    _position = v;
}
