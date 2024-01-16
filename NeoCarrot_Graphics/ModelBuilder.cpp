#include "ModelBuilder.h"

#include "D3D11Context_mk2.h"
#include "FBXLoader.h"

#include "D3Devices.h"
#include "Transpose.h"
#include "IndexBuffer.h"
#include "Effect.h"
#include "InputLayout.h"
#include "Camera3D.h"
#include "CameraPtr.h"
#include "GridScript.h"
#include "BoxScript.h"

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

ModelBuilder ModelBuilder::AddBoxcript(loader::FbxLoader* fbxLodaer)
{
    _entity->AddComponent<BoxScript>(_entity, fbxLodaer);
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