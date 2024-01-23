#pragma once

#include "AxisScript.h"
#include "Entity.h"
#include "EntityEnum.h"

#include <memory>
#include <string>
#include <vector>
#include <d3dcommon.h>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct D3D11_INPUT_ELEMENT_DESC;
struct ID3D11RasterizerState;

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace loader
{
class FbxLoader;
}

namespace graphics
{
class Camera3D;
class D3D11Context_mk2;

// 본문
class ModelBuilder
{
public:
    ModelBuilder(const size_t&& id,
                 const char* name,
                 core::Tag&& tag,
                 core::Layer&& layer);

    ModelBuilder AddD3Device(const D3D11Context_mk2* d3d11context);
    ModelBuilder AddTransform();
    template<typename T>
    ModelBuilder AddVertexBuffer();
    ModelBuilder AddIndexBuffer();
    ModelBuilder AddEffect(std::wstring fileName);
    ModelBuilder AddVertexLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>* desc);
    ModelBuilder AddCamera(Camera3D* camera);
    ModelBuilder AddTexture(std::wstring filename);

    ModelBuilder AddTransform_mk2(Camera3D* camera);

    template<typename T>
    ModelBuilder AddVertexResource(std::wstring shaderFile,
                                     const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc);

    ModelBuilder AddIndexBuffer_mk2();

    //template<typename T>
    //ModelBuilder AddContantBuffer();
    ModelBuilder AddContantBufferWVP();

    ModelBuilder AddFbxLoad(loader::FbxLoader* fbxLodaer, std::string shaderFile);

    ModelBuilder AddRenderor(D3D_PRIMITIVE_TOPOLOGY primitiveTopology);

    /// 스크립트
    ModelBuilder AddAxisScript();
    ModelBuilder AddGridScript();
    ModelBuilder AddBoxScript(loader::FbxLoader* fbxLodaer);
    ModelBuilder AddTriangleScript();
    ModelBuilder AddRainbowScript();

    // 제품 반환
    EntityPtr Build();

private:
    EntityPtr _entity;
};

} // namespace graphics

#include "ModelBuilder.inl"