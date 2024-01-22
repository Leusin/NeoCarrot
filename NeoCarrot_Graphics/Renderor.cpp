#include "Renderor.h"

#include "D3Devices.h"
#include "IndexBuffer_mk2.h"
#include "VertexResource.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
Renderor::Renderor(EntityPtr entityPtr, D3D_PRIMITIVE_TOPOLOGY primitiveTopology)
    : GetEntity(EntityPtr(entityPtr))
    , _d3devices{ GetComponent<graphics::D3Devices>() }
    , _primitiveTopology(primitiveTopology)
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Renderor Component\n";
#endif // _DEBUG;
}
void Renderor::Update(float dt)
{
    UpdateRender();
}

//////////////////////////////////////////////////////////////////////
void Renderor::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY primitiveTopology)
{
    _primitiveTopology = primitiveTopology;
}

//////////////////////////////////////////////////////////////////////
void Renderor::UpdateRender()
{
    auto* deviceContext = _d3devices->GetDeviceContext();

    deviceContext->IASetPrimitiveTopology(_primitiveTopology);
    //deviceContext->DrawIndexed(36, 0, 0);


    auto* indexBuf = GetComponent<IndexBuffer_mk2>();
    //auto* vetexBuf = GetComponent<VertexResource<void>>();


    //for (unsigned int i = 0; i < vetexBuf->_vertexOffset.size(); ++i)
    {
        //deviceContext->DrawIndexed(indexBuf->_indexCount[i], // �ε��� ����
        //                           indexBuf->_indexOffset[i], // �ε��� ���� ��ġ
        //                           vetexBuf->_vertexOffset[i]); // ���ε��� �������� ���� ��
    }
}

} // namespace graphics