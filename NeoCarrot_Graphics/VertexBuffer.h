#pragma once

#include "IComponent.h"

#include <d3d11.h>
#include <vector>
#include <wrl.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
template <typename V>
class VertexBuffer
{
public:
    VertexBuffer();

    void BuildBuffers();


private:
    //ID3D11Device* _d3dDevice;

    // 버텍스버퍼
    Microsoft::WRL::ComPtr<ID3D11Buffer> _vb;
    std::vector<V>                       _vertices;
    std::vector<int>                     _vertexOffset;
    UINT                                 _totalVertexCount;
};

template <typename V>
inline VertexBuffer<V>::VertexBuffer()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd VertexBuffer Component\n";
#endif // _DEBUG
}

template <typename V>
inline void VertexBuffer<V>::BuildBuffers()
{
    //D3D11_BUFFER_DESC vbd;
    //vbd.Usage          = D3D11_USAGE_IMMUTABLE;
    //vbd.ByteWidth      = sizeof(V) * _totalVertexCount;
    //vbd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    //vbd.CPUAccessFlags = 0;
    //vbd.MiscFlags      = 0;
    //D3D11_SUBRESOURCE_DATA vinitData;
    //vinitData.pSysMem = &_vertices[0];
    //_d3dDevice->CreateBuffer(&vbd, &vinitData, _vb.GetAddressOf());
}

} // namespace graphics