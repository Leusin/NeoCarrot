#include "ModelFactory.h"

#include "FbxLoader.h"

#include "Entity.h"
#include "D3D11Context_mk2.h"
#include "Devices.h"
#include "ModelBuilder.h"
#include "Camera3D.h"
#include "StructedBuffer.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

ModelFactory::ModelFactory(D3D11Context_mk2* d3d11context, Camera3D* camera) 
    : _d3d11context(d3d11context)
    , _camera(camera)
    , _fbxLoader(std::make_unique<loader::FbxLoader>())
{
#if defined(DEBUG) || defined(_DEBUG)
    std::cout << "\t\tModelFactory Constructed\n";
#endif
}

EntityPtr ModelFactory::CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name)
{
    switch (enumTypeEntity)
    {
        case core::GameObect::AXIS:
            return CreateAxis(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::BOX:
            return CreateBox(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::GRID:
            return CreateGrid(std::forward<const size_t>(id), std::move(name));
        default:
            break;
    }

    return nullptr;
}

EntityPtr ModelFactory::CreateGrid(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id), std::move(name), core::Tag::GIZMO, core::Layer::DEBUGINFO);

    auto grid = builder.AddD3Device(_d3d11context)
                    .AddTransform()
                    .AddCamera(_camera)
                    .AddVertexBuffer<PosCol>()
                    .AddIndexBuffer()
                    .AddEffect({L"../NeoCarrot_Graphics/FX/color.fxo"})
                    .AddVertexLayout(&PosColorDesc)
                    .AddGridScript()
                    .Build();

    return grid;
}

EntityPtr ModelFactory::CreateAxis(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id), std::move(name), core::Tag::GIZMO, core::Layer::DEBUGINFO);

    auto axis = builder
                    .AddD3Device(_d3d11context)
                    .AddTransform()
                    .AddCamera(_camera)
                    .AddVertexBuffer<PosCol>()
                    .AddIndexBuffer()
                    .AddEffect({L"../NeoCarrot_Graphics/FX/color.fxo"})
                    .AddVertexLayout(&PosColorDesc)
                    .AddAxisScript()
                    .Build();

    return axis;
}

EntityPtr ModelFactory::CreateBox(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id), std::move(name), core::Tag::MESHOBJ, core::Layer::FORGROUND);

    auto box = builder
                   .AddD3Device(_d3d11context)
                   .AddTransform()
                   .AddCamera(_camera)
                   .AddVertexBuffer<PosNormal>()
                   .AddIndexBuffer()
                   .AddEffect({L"../NeoCarrot_Graphics/FX/color.fxo"})
                   .AddVertexLayout(&PosNormalTexWeightsBoneidxDesc)
                   .AddBoxcript(_fbxLoader.get())
                   // 이펙트, 조명, 테크
                   // 변환 행렬, 카메라 위치, 월드 좌표
                   // 머터리얼
                   //
                   // 텍스처
                   .Build();

    return box;
}

} // namespace graphics