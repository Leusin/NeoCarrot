#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <directxmath.h>
#include <d3dx11effect.h>
#include <string>
#include <wrl.h>

namespace graphics
{
struct DirectionalLight
{
    DirectionalLight()
    {
        ZeroMemory(this, sizeof(this));
    }

    DirectX::XMFLOAT4 Ambient;
    DirectX::XMFLOAT4 Diffuse;
    DirectX::XMFLOAT4 Specular;
    DirectX::XMFLOAT3 Direction;
    float    Pad; // Pad the last float so we can set an array of lights if we wanted.
};

struct Material
{
    Material()
    {
        ZeroMemory(this, sizeof(this));
    }

    DirectX::XMFLOAT4 Ambient;
    DirectX::XMFLOAT4 Diffuse;
    DirectX::XMFLOAT4 Specular; // w = SpecPower
    DirectX::XMFLOAT4 Reflect;
};

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

    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>         _worldViewProj{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>         _world{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>         _worldInvTranspose{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectVectorVariable>         _eyePosW{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectVariable>               _dirLights{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectVariable>               _mat{nullptr};


    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable>         _texTransform{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseMap{nullptr};


    void SetWorldViewProj(DirectX::CXMMATRIX M) { _worldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(DirectX::CXMMATRIX M) { _world->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(DirectX::CXMMATRIX M) { _worldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const DirectX::XMFLOAT3& v) { _eyePosW->SetRawValue(&v, 0, sizeof(DirectX::XMFLOAT3)); }
	void SetDirLights(const DirectionalLight* lights) { _dirLights->SetRawValue(lights, 0, 3 * sizeof(DirectionalLight)); }
	void SetMaterial(const Material& mat) { _mat->SetRawValue(&mat, 0, sizeof(Material)); }

	/// 텍스쳐 추가
	void SetTexTransform(DirectX::CXMMATRIX M) { _texTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex) { _diffuseMap->SetResource(tex); }

private:
    void AwakeReadFile();
    void AwakeGetTechniqueByName();

    bool CompileFromFile();

    void UpdateSetWorldViewProj();


    D3Devices* _d3device{nullptr};

    std::wstring _fileName;
};

} // namespace graphics