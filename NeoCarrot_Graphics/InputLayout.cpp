#include "InputLayout.h"

#include "D3Devices.h"
#include "Effect.h"

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DE

namespace graphics
{
InputLayout::InputLayout(EntityPtr entityPtr, const std::vector<D3D11_INPUT_ELEMENT_DESC>* vertexDesc)
: GetEntity(EntityPtr(entityPtr))
    , _d3device{GetComponent<graphics::D3Devices>()}
    , _effect{GetComponent<graphics::Effect>()}
    , _vertexDescVec{vertexDesc}
{
    assert(_d3device && "InputLayout ���� D3Devices �� ã�� �� ����");
    assert(_effect && "InputLayout ���� Effect �� ã�� �� ����");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd InputLayout Component\n";
#endif // _DEBUG
}

void InputLayout::Awake()
{
    D3DX11_PASS_DESC passDesc;

    _effect->_tech->GetPassByIndex(0)->GetDesc(&passDesc);

    _d3device->GetDevice()->CreateInputLayout(_vertexDescVec->data(),
                                              static_cast<UINT>(_vertexDescVec->size()),
                                              passDesc.pIAInputSignature,
                                              passDesc.IAInputSignatureSize,
                                              _inputLayout.GetAddressOf());


}

void InputLayout::Update(float dt)
{
    SetInputLayout();
}

void InputLayout::SetInputLayout()
{
    _d3device->GetDeviceContext()->IASetInputLayout(_inputLayout.Get());
};

} // namespace graphics