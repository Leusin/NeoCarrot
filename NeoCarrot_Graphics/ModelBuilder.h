#pragma once

#include "EntityEnum.h"
#include "Entity.h"
#include "VertexBuffer.h"
#include "AxisScript.h"

#include <memory>
#include <string>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct D3D11_INPUT_ELEMENT_DESC;
struct ID3D11RasterizerState;

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace loader{ class FbxLoader; }

namespace graphics
{
class Camera3D;

// 본문
class ModelBuilder
{
public:
    ModelBuilder(const size_t&& id, const char* name, core::Tag&& tag, core::Layer&& layer);
    
    ModelBuilder AddD3Device(const D3D11Context_mk2* d3d11context);
    
    ModelBuilder AddTransform();
    
    template <typename T>
    ModelBuilder AddVertexBuffer();

    ModelBuilder AddIndexBuffer();

    ModelBuilder AddEffect(std::wstring fileName);

    ModelBuilder AddVertexLayout(const D3D11_INPUT_ELEMENT_DESC* desc);

    ModelBuilder AddCamera(Camera3D* camera);

    /// 스크립트

    ModelBuilder AddAxisScript();
    ModelBuilder AddGridScript();
    ModelBuilder AddBoxcript(loader::FbxLoader* fbxLodaer);

    // 제품 반환
    EntityPtr Build();

private:

    EntityPtr _entity;
};

template <typename T>
inline ModelBuilder ModelBuilder::AddVertexBuffer()
{
    _entity->AddComponent<VertexBuffer<T>>(_entity);

    return *this;
}

} // namespace graphics