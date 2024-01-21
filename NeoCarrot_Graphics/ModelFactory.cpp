#include "ModelFactory.h"

#include "Camera3D.h"
#include "Entity.h"
#include "FbxLoader.h"
#include "ModelBuilder.h"
#include "components.h"

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

EntityPtr ModelFactory::CreateEntity(core::GameObect enumTypeEntity,
                                     const size_t&& id,
                                     const char* name)
{
    switch (enumTypeEntity)
    {
        case core::GameObect::AXIS:
            return CreateAxis(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::BOX:
            return CreateBox(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::BOX2:
            return CreateBox2(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::GRID:
            return CreateGrid(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::Triangle:
            return CreateTriangle(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::RainbowBox:
            return CreateRainbowBox(std::forward<const size_t>(id), std::move(name));
        default:
            break;
    }

    return nullptr;
}

EntityPtr ModelFactory::CreateGrid(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::GIZMO,
                                core::Layer::DEBUGINFO);

    auto grid = builder.AddD3Device(_d3d11context)
                    .AddTransform()
                    .AddCamera(_camera)
                    .AddVertexBuffer<PosCol>()
                    .AddIndexBuffer()
                    .AddEffect({ L"../NeoCarrot_Graphics/FX/color.fxo" })
                    .AddVertexLayout(&PosColorDesc)
                    .AddGridScript()
                    .Build();

    return grid;
}

EntityPtr ModelFactory::CreateAxis(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::GIZMO,
                                core::Layer::DEBUGINFO);

    auto axis = builder.AddD3Device(_d3d11context)
                    .AddTransform()
                    .AddCamera(_camera)
                    .AddVertexBuffer<PosCol>()
                    .AddIndexBuffer()
                    .AddEffect({ L"../NeoCarrot_Graphics/FX/color.fxo" })
                    .AddVertexLayout(&PosColorDesc)
                    .AddAxisScript()
                    .Build();

    return axis;
}

EntityPtr ModelFactory::CreateBox(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::MESHOBJ,
                                core::Layer::FORGROUND);

    auto box = builder.AddD3Device(_d3d11context)
                   .AddTransform()
                   .AddCamera(_camera)
                   .AddVertexBuffer<PosCol>()
                   .AddIndexBuffer()
                   .AddEffect({ L"../NeoCarrot_Graphics/FX/color.cso" })
                   .AddVertexLayout(&PosColorDesc)
                   //.AddTexture(L"../NeoCarrot_Graphics/Texture/WoodCrate01.dds")
                   .AddBoxScript(_fbxLoader.get())
                   .Build();

    return box;
}

EntityPtr ModelFactory::CreateBox2(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::MESHOBJ,
                                core::Layer::FORGROUND);

    auto box = builder.AddD3Device(_d3d11context)
                   .AddTransform()
                   .AddCamera(_camera)
                   .AddShader(L"../NeoCarrot_Graphics/HLSL/VertexShader.hlsl",
                              L"../NeoCarrot_Graphics/HLSL/PixelShader.hlsl")
                   .Build();

    return box;
}

EntityPtr ModelFactory::CreateRainbowBox(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::MESHOBJ,
                                core::Layer::FORGROUND);

    auto box = builder.AddD3Device(_d3d11context)
                   .AddTransform()
                   .AddCamera(_camera)
                   .AddRainbowScript()
                   .Build();

    return box;
}

EntityPtr ModelFactory::CreateTriangle(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::MESHOBJ,
                                core::Layer::FORGROUND);

    auto triangle = builder.AddD3Device(_d3d11context)
                        .AddTransform()
                        .AddCamera(_camera)
                        .AddTriangleScript()
                        .Build();

    return triangle;
}

} // namespace graphics