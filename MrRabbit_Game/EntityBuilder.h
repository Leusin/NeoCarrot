/// ������ ���� ��ƼƼ�� �ʿ�� �ϴ� ������Ʈ�� ������ �ִ�
/// ���� Ŭ������ �Դϴ�.
/// 
/// 2024-01-09

#pragma once

#include "EntityEnum.h"

#include <memory>

namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr = std::shared_ptr<core::Entity<game::Tag, game::Layer>>;

namespace game
{

class EntityBuilder
{
public:
    EntityBuilder(const size_t&& id, const char* name, Tag&& tag, Layer&& layer);

public:
    EntityBuilder AddTransform();
    EntityBuilder AddCamera();

    /// 

    EntityBuilder AddCameraScript();

    // ��ǰ ��ȯ
    EntityPtr     Build();

private:
    EntityPtr _entity;
};

} // namespace game