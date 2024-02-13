#include "AnimateRotateY.h"

#include "Transpose_mk2.h"

#ifdef _DEBUG
#include <iostream>
#include "ColoredBox2Script.h"
#endif // _DEBUG

namespace graphics
{

ColoredBox2Script::ColoredBox2Script(EntityPtr entityPtr)
    : GetEntity{ EntityPtr(entityPtr) }
    , _transpose{ GetComponent<Transpose_mk2>() }
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd ColoredBox2Script Component\n";
#endif // _DEBUG;
}

void ColoredBox2Script::Update(float dt)
{
    UpdateTick(dt);
    UpdateAnimation();
}

//////////////////////////////////////////////////////////////////////
void ColoredBox2Script::UpdateTick(float dt)
{
    _t1 += dt * -1.f;
    _t2 += dt * -2.f;
}

//////////////////////////////////////////////////////////////////////
void ColoredBox2Script::UpdateAnimation()
{
    DirectX::XMMATRIX mSpin  = DirectX::XMMatrixRotationZ(_t1);
    DirectX::XMMATRIX mOrbit = DirectX::XMMatrixRotationY(_t2);
    DirectX::XMMATRIX mTranslate = DirectX::XMMatrixTranslation(-4.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX mScale = DirectX::XMMatrixScaling(0.3f, 0.3f, 0.3f);

    _transpose->SetWorld(mScale * mSpin * mTranslate * mOrbit);
}

} // namespace graphics