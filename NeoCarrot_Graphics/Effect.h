#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <d3dx11effect.h>
#include <string>
#include <wrl.h>

namespace graphics
{
// 전방 선언
class D3Devices;

// 본문
class Effect : public core::IComponent, virtual core::GetEntity
{
public:
    Effect(EntityPtr entityPtr, std::wstring fileName);

    void Awake() override;
    void Update(float dt) override;

    void GetTechniqueDesc(D3DX11_TECHNIQUE_DESC* dec);

    // 이펙트
    Microsoft::WRL::ComPtr<ID3DX11Effect> _fx{nullptr};

    // pass
    Microsoft::WRL::ComPtr<ID3DX11EffectTechnique> _tech{nullptr};

    // 상수 버퍼
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable> _fxWorldViewProj{nullptr};

    Microsoft::WRL::ComPtr<ID3DX11EffectVariable>               _dirLights{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectVectorVariable>         _eyePosW{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>         _world{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>         _worldInvTranspose{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>         _worldViewProj{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>         _texTransform{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectVariable>               _material{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseMap{nullptr};

private:
    void SetWorldViewProj();
    bool CompileFromFile();
    void ReadFile();

    D3Devices* _d3device{nullptr};

    std::wstring _fileName;
};

} // namespace graphics