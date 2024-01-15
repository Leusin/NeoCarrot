#include "ModelFactory.h"

#include "../UnityLike_Core/Entity.h"
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
        default:
            break;
    }

    return nullptr;
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
                    .AddVertexLayout(PosColorDesc)
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
                   .AddIndexBuffer()
                   // dc, inputlayout(fx 와 초기화) , Renderstate
                   // GeometryBuffers - (버텍스 & 인덱스)버퍼, 버텍스 데이터
                   // 이펙트, 조명, 테크
                   // 변환 행렬, 카메라 위치, 월드 좌표
                   // 머터리얼
                   //
                   // 텍스처
                   .Build();

    return box;
}

} // namespace graphics