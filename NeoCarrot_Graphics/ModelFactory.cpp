#include "ModelFactory.h"

#include "../UnityLike_Core/Entity.h"
#include "ResourceManager.h"
#include "ModelBuilder.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
ModelFactory::ModelFactory(ResourceManager* resourceManager) : _resourceManager(resourceManager)
{
#if defined(DEBUG) || defined(_DEBUG)
    std::cout << "\t\tModelFactory Constructed\n";
#endif
}

EntityPtr ModelFactory::CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name)
{
    switch (enumTypeEntity)
    {
        case core::GameObect::BOX:
            return CreateAxis(std::forward<const size_t>(id), std::move(name));
        case core::GameObect::AXIS:
            return CreateBox(std::forward<const size_t>(id), std::move(name));
        default:
            break;
    }

    return nullptr;
}
EntityPtr ModelFactory::CreateAxis(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(
        std::forward<const size_t>(id), 
        std::move(name), 
        core::Tag::GIZMO, 
        core::Layer::DEBUGINFO);

    auto axis = builder
                   .AddTransform()
                   .Build();

    return axis;
}
EntityPtr ModelFactory::CreateBox(const size_t&& id, const char* name)
{
    auto builder = ModelBuilder(
        std::forward<const size_t>(id), 
        std::move(name), 
        core::Tag::MESHOBJ, 
        core::Layer::FORGROUND);

    auto box = 
        builder
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