#pragma once

#include <directxmath.h>
#include <d3d11.h>

class Model
{
private:
    struct VertexType
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT4 color;
    };

public:
    bool Initialize(ID3D11Device* device);
    void Shutdown();
    void Render(ID3D11DeviceContext* deviceContext);

    int           m_indexCount   = 0;
private:
    ID3D11Buffer* m_vertexBuffer = nullptr;
    ID3D11Buffer* m_indexBuffer  = nullptr;
    int           m_vertexCount  = 0;
};