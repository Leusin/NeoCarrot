#include "VertexLayout.h"

#include "D3Devices.h"
#include "Effect.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DE

namespace graphics
{
VertexLayout::VertexLayout(EntityPtr entityPtr, const D3D11_INPUT_ELEMENT_DESC* vertexDesc) 
    : GetEntity(EntityPtr(entityPtr))
    , _d3device{GetComponent<graphics::D3Devices>()}
    , _effect{GetComponent<graphics::Effect>()}
    , _vertexDesc{vertexDesc}
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd VertexLayout Component\n";
#endif // _DEBUG
}

void VertexLayout::Awake()
{
    D3DX11_PASS_DESC passDesc;
    _effect->_tech->GetPassByIndex(0)->GetDesc(&passDesc);

    _d3device->GetDevice()->CreateInputLayout(_vertexDesc,
                                              2,
                                              passDesc.pIAInputSignature,
                                              passDesc.IAInputSignatureSize,
                                              _inputLayout.GetAddressOf());

};

} // namespace graphics