#include "ModelFactory.h"

#include "../UnityLike_Core/Entity.h"
#include "D3D11Context.h"
#include "ModelBuilder.h"
#include "ResourceManager.h"
#include "Camera3D.h"
#include "D3D11RenderStates.h"
#include "VertexStruct.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
ModelFactory::ModelFactory(ResourceManager* resourceManager, Camera3D* camera) :
_resourceManager(resourceManager),
_camera(camera)
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

    auto axis = builder.AddD3Device(_resourceManager->_d3d11->Divice(), _resourceManager->_d3d11->DiviceContext(), _resourceManager->_renderState->WireFrame())
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