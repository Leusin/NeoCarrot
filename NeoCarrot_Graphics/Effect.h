#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <d3dx11effect.h>
#include <wrl.h>
#include <string>

namespace graphics
{
// ���� ����
class D3Devices;

// ����
class Effect : public core::IComponent, virtual core::GetEntity
{
public:
    Effect(EntityPtr entityPtr, std::wstring fileName);

    void Awake() override;
    void Update(float dt) override;

    void GetTechniqueDesc(D3DX11_TECHNIQUE_DESC* dec);

     // ����Ʈ
    Microsoft::WRL::ComPtr<ID3DX11Effect>               _fx{ nullptr };
    Microsoft::WRL::ComPtr<ID3DX11EffectTechnique>      _tech{ nullptr };

    // ��� ����
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable> _fxWorldViewProj{ nullptr };

private:

    void SetWorldViewProj();

    D3Devices* _d3device{nullptr};

    std::wstring _fileName;
};

} // namespace graphics