#include "ModelFactory.h"

#include "../UnityLike_Core/Entity.h"
#include "D3D11Context_mk2.h"
#include "Devices.h"
#include "ModelBuilder.h"
#include "Camera3D.h"
#include "VertexStruct.h"

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
                    .AddVertexBuffer<graphics::PosCol>()
                    .AddIndexBuffer()
                    .AddTransform()
                    .AddEffect({L"../NeoCarrot_Graphics/FX/color.fxo"})
                    .AddVertexLayout(PosColorDesc)
                    .AddAxisScript()
                    .AddCamera(_camera)
                    .Build();

    return axis;
}
EntityPtr ModelFactory::CreateBox(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(std::forward<const size_t>(id), std::move(name), core::Tag::MESHOBJ, core::Layer::FORGROUND);

    auto box = builder
                   // dc, inputlayout(fx �� �ʱ�ȭ) , Renderstate
                   // GeometryBuffers - (���ؽ� & �ε���)����, ���ؽ� ������
                   // ����Ʈ, ����, ��ũ
                   // ��ȯ ���, ī�޶� ��ġ, ���� ��ǥ
                   // ���͸���
                   //
                   // �ؽ�ó
                   .Build();

    return box;
}
} // namespace graphics