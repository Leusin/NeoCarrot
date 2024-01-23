#pragma once

#include "AxisScript.h"
#include "Entity.h"
#include "EntityEnum.h"
#include "FBXLoader.h"

#include <d3dcommon.h>
#include <memory>
#include <string>
#include <vector>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct D3D11_INPUT_ELEMENT_DESC;
struct ID3D11RasterizerState;

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

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
    template<typename T>
    ModelBuilder AddVertexBuffer();
    ModelBuilder AddIndexBuffer();
    ModelBuilder AddEffect(std::wstring fileName);
    ModelBuilder AddVertexLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>* desc);
    // ModelBuilder AddTexture(std::wstring filename);
    // ModelBuilder AddTransform();
    // ModelBuilder AddCamera(Camera3D* camera);

    //
    // 리메이크한 컴포넌트들
    // 2024-01-23

    ModelBuilder AddTranspose_mk2(Camera3D* camera);

    ModelBuilder AddVertexResourceNol(std::wstring shaderFile);
    ModelBuilder AddVertexResourcePos(std::wstring shaderFile);
    ModelBuilder AddIndexBuffer_mk2();
    ModelBuilder AddContantBufferTutorial05();
    ModelBuilder AddContantBufferTutorial06();
    ModelBuilder AddFbxLoad(loader::FbxLoader* fbxLodaer, std::string shaderFile);
    ModelBuilder AddRenderor(D3D_PRIMITIVE_TOPOLOGY primitiveTopology);
    ModelBuilder AddAinmateRotateY(float speed);
    ModelBuilder AddAinmateRotateZ(float speed);
    ModelBuilder GetAddFbxMeshNol(loader::FbxLoader* fbxLodaer, std::string shaderFile);
    // ModelBuilder AddContantBufferLight();

    /// 스크립트
    ModelBuilder AddAxisScript();
    ModelBuilder AddGridScript();
    ModelBuilder AddRainbowScript();
    ModelBuilder AddColoredBox2Script();
    ModelBuilder AddScriptTutorial06();
    //ModelBuilder AddLightBox1Script();
    //ModelBuilder AddBoxScript(loader::FbxLoader* fbxLodaer);
    //ModelBuilder AddTriangleScript();

    // 제품 반환
    EntityPtr Build();

private:
    EntityPtr _entity;

private:
    template<typename T>
    ModelBuilder AddVertexResource(std::wstring shaderFile,
                                   const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc);
};

} // namespace graphics

#include "ModelBuilder.inl"