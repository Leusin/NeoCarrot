#include "Model.h"

#include <SpriteFont.h>

bool Model::Initialize(ID3D11Device* device)
{
    //?����?�迭��?����?����?�����մϴ�.
    m_vertexCount = 4;

    //?�ε���?�迭��?�ε���?����?�����մϴ�.
    m_indexCount = 6;

    //?����?�迭��?�����.
    VertexType* vertices = new VertexType[m_vertexCount];
    if (!vertices)
    {
        return false;
    }

    //?�ε���?�迭��?����ϴ�.
    unsigned long* indices = new unsigned long[m_indexCount];
    if (!indices)
    {
        return false;
    }

    //?����?�迭��?�����͸�?�����մϴ�.
    //?�簢��
    vertices[0].position = DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f);
    //?bottom?left.
    vertices[0].color    = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    vertices[1].position = DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f);
    //?Top?left
    vertices[1].color    = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    vertices[2].position = DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f);
    //?top?right.
    vertices[2].color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[3].position = DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f);
    //?bottom?right.
    vertices[3].color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

    //?�簢��
    indices[0] = 0;
    //?Bottom?left;
    indices[1] = 1;
    //?Top?left;
    indices[2] = 2;
    //?Top?right;
    indices[3] = 2;
    //?Top?right;
    indices[4] = 3;
    //?Bottom?right;
    indices[5] = 0;
    //?Bottom?left;

    //?����?������?description?�ۼ�.
    D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth           = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags      = 0;
    vertexBufferDesc.MiscFlags           = 0;
    vertexBufferDesc.StructureByteStride = 0;

    //?����?�����͸�?����Ű��?����?���ҽ�?����ü��?�ۼ��Ѵ�.
    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem          = vertices;
    vertexData.SysMemPitch      = 0;
    vertexData.SysMemSlicePitch = 0;

    //?����?����?���۸�?����ϴ�.
    device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

    //?�ε���?����?description?����
    D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth           = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags      = 0;
    indexBufferDesc.MiscFlags           = 0;
    indexBufferDesc.StructureByteStride = 0;

    //?�ε���?�����͸�?����Ű��?����?���ҽ�?����ü?�ۼ�
    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem          = indices;
    indexData.SysMemPitch      = 0;
    indexData.SysMemSlicePitch = 0;

    //?�ε���?���۸�?�����մϴ�.
    device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);

    //?��������?�ε���?����?����
    delete[] vertices;
    delete[] indices;

    return true;
}

void Model::Shutdown()
{
    m_indexBuffer->Release();
    m_vertexBuffer->Release();
}

void Model::Render(ID3D11DeviceContext* deviceContext)
{
    unsigned int stride;
    unsigned int offset;

    stride = sizeof(VertexType);
    offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
    deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
