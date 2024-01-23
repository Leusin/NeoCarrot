#include "ModelFactory.h"

#include "Camera3D.h"
#include "Entity.h"
#include "FbxLoader.h"
#include "ModelBuilder.h"

// 임시로 여기둔다.. 이거 열면 래핑한 이유가 없어진다...
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
        case core::GameObect::GRID:
            return CreateGrid(std::forward<const size_t>(id), std::move(name));
        // case core::GameObect::BOX:
        //     return CreateBox(std::forward<const size_t>(id), std::move(name));
        // case core::GameObect::TRIANGLE:
        //     return CreateTriangle(std::forward<const size_t>(id), std::move(name));
        // case core::GameObect::RAINBOWBOX:
        //     return CreateRainbowBox(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::TUTORIAL04:
            return CreateTutorial04(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::TUTORIAL05:
            return CreateTutorial05(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::TUTORIAL06:
            return CreateTutorial06(std::forward<const size_t>(id), std::move(name));
        default:
            assert(true && "메시를 만들 수 있는 개체가 아님");
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
                    .AddTranspose_mk2(_camera)
                    .AddVertexBuffer<Col>()
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
                    .AddTranspose_mk2(_camera)
                    .AddVertexBuffer<Col>()
                    .AddIndexBuffer()
                    .AddEffect({ L"../NeoCarrot_Graphics/FX/color.fxo" })
                    .AddVertexLayout(&PosColorDesc)
                    .AddAxisScript()
                    .Build();

    return axis;
}

// EntityPtr ModelFactory::CreateBox(const size_t&& id, const char* name)
//{
//     auto builder = ModelBuilder(std::forward<const size_t>(id),
//                                 std::move(name),
//                                 core::Tag::MESHOBJ,
//                                 core::Layer::FORGROUND);
//
//     auto box = builder.AddD3Device(_d3d11context)
//                    .AddTranspose_mk2(_camera)
//                    .AddVertexBuffer<Col>()
//                    .AddIndexBuffer()
//                    .AddEffect({ L"../NeoCarrot_Graphics/FX/color.cso" })
//                    .AddVertexLayout(&PosColorDesc)
//                    //.AddTexture(L"../NeoCarrot_Graphics/Texture/WoodCrate01.dds")
//                    .AddBoxScript(_fbxLoader.get())
//                    .Build();
//
//     return box;
// }

/*
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
*/

EntityPtr ModelFactory::CreateTutorial04(const size_t&& id, const char* name)
{

    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::MESHOBJ,
                                core::Layer::FORGROUND);

    auto box = builder.AddD3Device(_d3d11context)
                   .AddTranspose_mk2(_camera)
                   .AddVertexResourcePos(L"../NeoCarrot_Graphics/HLSL/Tutoroal04.hlsl")
                   .AddIndexBuffer_mk2()
                   .AddContantBufferTutorial05()
                   .AddFbxLoad(_fbxLoader.get(),
                               "../NeoCarrot_Graphics/FBX/a.fbx")
                   .AddAinmateRotateY(1.f)
                   .AddRenderor(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
                   .Build();

    return box;
}

EntityPtr ModelFactory::CreateTutorial05(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::MESHOBJ,
                                core::Layer::FORGROUND);

    auto box = builder.AddD3Device(_d3d11context)
                   .AddTranspose_mk2(_camera)
                   .AddVertexResourcePos(L"../NeoCarrot_Graphics/HLSL/Tutoroal04.hlsl")
                   .AddIndexBuffer_mk2()
                   .AddContantBufferTutorial05()
                   .AddFbxLoad(_fbxLoader.get(),
                               "../NeoCarrot_Graphics/FBX/a.fbx")
                   .AddColoredBox2Script()
                   .AddRenderor(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
                   .Build();

    return box;
}

EntityPtr ModelFactory::CreateTutorial06(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::MESHOBJ,
                                core::Layer::FORGROUND);

    auto box = builder.AddD3Device(_d3d11context)
                   .AddTranspose_mk2(_camera)
                   //.AddVertexResourceNol(L"../NeoCarrot_Graphics/HLSL/Tutoroal06.hlsl")
                   //.AddIndexBuffer_mk2()
                   //.AddContantBufferTutorial06()
                   //.GetAddFbxMeshNol(_fbxLoader.get(),
                   //            "../NeoCarrot_Graphics/FBX/a.fbx")
                   .AddScriptTutorial06()
                   .Build();

    return box;
}

/*
EntityPtr ModelFactory::CreateLightBox1(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id),
                                std::move(name),
                                core::Tag::MESHOBJ,
                                core::Layer::FORGROUND);

    auto box = builder.AddD3Device(_d3d11context)
                   .AddTranspose_mk2(_camera)
                   .AddVertexResource<
                       Col>(L"../NeoCarrot_Graphics/HLSL/Lighting.hlsl",
PosNormalDesc) .AddIndexBuffer_mk2() .AddContantBufferWVP()
                   .AddContantBufferLight()
                   .GetAddFbxMesh(_fbxLoader.get(),
                               "../NeoCarrot_Graphics/FBX/a.fbx")
                   .AddAinmateRotateY(1.f)
                   .AddLightBox1Script()
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
*/

} // namespace graphics