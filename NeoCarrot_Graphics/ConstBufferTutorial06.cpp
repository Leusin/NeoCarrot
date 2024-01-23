#include "ConstBufferTutorial06.h"

#include "Transpose_mk2.h"
#include "components.h"

#include <directxmath.h>

#include <cassert>

namespace graphics
{
ConstBufferTutorial06::ConstBufferTutorial06(EntityPtr entityPtr)
    : ConstantBuffer<ConstBuffLit>(EntityPtr(entityPtr))
{
    InitializeVariable();
}

void ConstBufferTutorial06::Awake()
{
    ConstantBuffer<ConstBuffLit>::Awake();
}

void ConstBufferTutorial06::Update(float dt)
{
    RotateAnimation();
    UpdateVariable();
    RenderLight();
    ConstantBuffer<ConstBuffLit>::Update(dt);
}

//////////////////////////////////////////////////////////////////////
void ConstBufferTutorial06::InitializeVariable()
{
    vLightDirs = {
        DirectX::XMFLOAT4(-0.577f, 0.577f, -0.577f, 1.0f),
        DirectX::XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f),
    };
    vLightColors = { DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),
                     DirectX::XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f) };
}

//////////////////////////////////////////////////////////////////////
void ConstBufferTutorial06::RotateAnimation()
{
    auto* Trans  = GetComponent<Transpose_mk2>();
    auto mRotate = Trans->GetWorld();

    assert(Trans);

    DirectX::XMVECTOR vLightDir = DirectX::XMLoadFloat4(&vLightDirs[1]);
    vLightDir                   = XMVector3Transform(vLightDir, mRotate);
    DirectX::XMStoreFloat4(&vLightDirs[1], vLightDir);
}

//////////////////////////////////////////////////////////////////////
void ConstBufferTutorial06::UpdateVariable()
{
    auto* deviceContext = _d3devices->GetDeviceContext();
    auto* Trans         = GetComponent<Transpose_mk2>();

    assert(Trans);

    ConstBuffLit cb;
    cb.mWorld         = XMMatrixTranspose(Trans->GetWorld());
    cb.mView          = XMMatrixTranspose(Trans->GetView());
    cb.mProjection    = XMMatrixTranspose(Trans->GetProj());
    cb.vLightDir[0]   = vLightDirs[0];
    cb.vLightDir[1]   = vLightDirs[1];
    cb.vLightColor[0] = vLightColors[0];
    cb.vLightColor[1] = vLightColors[1];
    cb.vOutputColor   = DirectX::XMFLOAT4(0, 0, 0, 0);
    deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
}

//////////////////////////////////////////////////////////////////////
void ConstBufferTutorial06::RenderLight()
{
    auto* deviceContext = _d3devices->GetDeviceContext();
    auto vertexResource = GetComponent<VertexResource<Nol>>();

    for (int m = 0; m < 2; m++)
    {
        float scalar = 0.5f;
        vLightDirs[m].x *= scalar;
        vLightDirs[m].y *= scalar;
        vLightDirs[m].z *= scalar;
        vLightDirs[m].w *= scalar;

        DirectX::XMMATRIX mLight = DirectX::XMMatrixTranslationFromVector(
            XMLoadFloat4(&vLightDirs[m]));

        DirectX::XMMATRIX mLightScale = DirectX::XMMatrixScaling(0.2f, 0.2f, 0.2f);
        mLight = mLightScale * mLight;

        // Update the world variable to reflect the current light
        _cb.mWorld       = XMMatrixTranspose(mLight);
        _cb.vOutputColor = vLightColors[m];
        deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &_cb, 0, 0);

        deviceContext->PSSetShader(vertexResource->_pixelShader.Get(), nullptr, 0);
        deviceContext->DrawIndexed(36, 0, 0);
    }
}

} // namespace graphics