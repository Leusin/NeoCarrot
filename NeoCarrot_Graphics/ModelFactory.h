#pragma once

#include "IFactory.h"

// 전방 선언
namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace loader{ class FbxLoader; }
namespace graphics
{
class Camera3D;
class D3D11Context_mk2;

// 본문
class ModelFactory : public core::IFactory
{
public:
    ModelFactory(D3D11Context_mk2* d3d11context, Camera3D* camera);

    EntityPtr CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name);

private:
    EntityPtr CreateGrid(const size_t&& id, const char* name);
    EntityPtr CreateAxis(const size_t&& id, const char* name);
    EntityPtr CreateBox(const size_t&& id, const char* name);
    EntityPtr CreateTriangle(const size_t&& id, const char* name);
    EntityPtr CreateRainbowBox(const size_t&& id, const char* name);
    EntityPtr CreateColoredBox1(const size_t&& id, const char* name);
    EntityPtr CreateColoredBox2(const size_t&& id, const char* name);

    D3D11Context_mk2* _d3d11context;
    Camera3D*        _camera;
    std::unique_ptr<loader::FbxLoader> _fbxLoader;
};

} // namespace graphics