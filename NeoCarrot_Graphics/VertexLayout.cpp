#include "VertexLayout.h"

#include "D3Device.h"
#include "Effect.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DE

namespace graphics
{

    

VertexLayout::VertexLayout(EntityPtr entityPtr, const D3D11_INPUT_ELEMENT_DESC* vertexDesc) :
_entity{EntityPtr(entityPtr)},
_d3device{_entity.lock()->GetComponent<graphics::D3Device>()},
_effect{_entity.lock()->GetComponent<graphics::Effect>()},
_vertexDesc{vertexDesc}
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd VertexLayout Component\n";
#endif // _DEBUG
};

void VertexLayout::Build()
{
    D3DX11_PASS_DESC passDesc;
    _effect->_tech->GetPassByIndex(0)->GetDesc(&passDesc);

    _d3device->Get()->CreateInputLayout(_vertexDesc,
                                  2,
                                  passDesc.pIAInputSignature,
                                  passDesc.IAInputSignatureSize,
                                  _inputLayout.GetAddressOf());
}

} // namespace graphics