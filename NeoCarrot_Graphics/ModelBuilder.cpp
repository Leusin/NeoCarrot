#include "ModelBuilder.h"

#include "D3D11Context_mk2.h"
#include "Devices.h"
#include "Camera3D.h"
#include "FBXLoader.h"

#include "components.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <d3d11.h>

namespace graphics
{
    
ModelBuilder::ModelBuilder(const size_t&& id, const char* name, core::Tag&& tag, core::Layer&& layer) :
_entity(std::make_shared<core::Entity<core::Tag, core::Layer>>(std::forward<const size_t>(id),
                                                               std::move(name),
                                                               std::move(tag),
                                                               std::move(layer)))
{
#ifdef _DEBUG
    std::cout << "\t\t\tCreate Graphics Entity ( " << name << ", " << static_cast<int>(id) << " ) \n";
#endif // _DEBUG
}
ModelBuilder ModelBuilder::AddD3Device(const D3D11Context_mk2* d3d11context)
{
    _entity->AddComponent<D3Devices>(d3d11context);

    return *this;
}

ModelBuilder ModelBuilder::AddTransform()
{
    _entity->AddComponent<Transpose>();

    return *this;
}

ModelBuilder ModelBuilder::AddIndexBuffer()
{
    _entity->AddComponent<IndexBuffer>(_entity);

    return *this;
}

ModelBuilder ModelBuilder::AddEffect(std::wstring fileName)
{
    _entity->AddComponent<Effect>(_entity, fileName);

    return *this;
}

ModelBuilder ModelBuilder::AddVertexLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>* desc)
{
    _entity->AddComponent<InputLayout>(_entity, desc);

    return *this;
}

ModelBuilder ModelBuilder::AddCamera(Camera3D* camera)
{
    _entity->AddComponent<CameraPtr>(_entity,camera);

    return *this;
}

ModelBuilder ModelBuilder::AddShader(std::wstring vsfile, std::wstring psfile)
{
    _entity->AddComponent<Shader>(_entity, vsfile, psfile);

    return *this;
}

ModelBuilder ModelBuilder::AddTexture(std::wstring filename)
{
    _entity->AddComponent<Texture>(_entity, filename);

    return *this;
}

ModelBuilder ModelBuilder::AddTransform_mk2(Camera3D* camera)
{

    _entity->AddComponent<Transpose_mk2>(camera);

    return *this;
}

ModelBuilder ModelBuilder::AddIndexBuffer_mk2()
{
    _entity->AddComponent<IndexBuffer_mk2>(_entity);
    return *this;
}

ModelBuilder ModelBuilder::AddRenderor()
{
    _entity->AddComponent<Renderor>(_entity);
    return *this;
}

ModelBuilder ModelBuilder::AddAxisScript()
{
    _entity->AddComponent<AxisScript>(_entity);

    return *this;
}

ModelBuilder ModelBuilder::AddGridScript()
{
    _entity->AddComponent<GridScript>(_entity);

    return *this;
}

ModelBuilder ModelBuilder::AddBoxScript(loader::FbxLoader* fbxLodaer)
{
    _entity->AddComponent<BoxScript>(_entity, fbxLodaer);
    return *this;
}

ModelBuilder ModelBuilder::AddTriangleScript()
{
    _entity->AddComponent<TriangleScript>(_entity);
    return *this;
}

ModelBuilder ModelBuilder::AddRainbowScript()
{
    _entity->AddComponent<RainbowBoxScript>(_entity);
    return *this;
}

EntityPtr ModelBuilder::Build()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tEnd build\n";
#endif // _DEBUG

    return _entity;
}

} // namespace graphics