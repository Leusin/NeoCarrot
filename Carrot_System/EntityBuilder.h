/// �������� ��ƼƼ�� �����ϴ� ���� Ŭ���� �Դϴ�.
/// ������ ���� ��ƼƼ�� �ʿ�� �ϴ� ������Ʈ�� �����մϴ�.
///
/// 2024-01-09

#pragma once

#include "EntityEnum.h"

#include <memory>

namespace core
{
template <typename T, typename U>
class Entity;
} // namespace core

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace game
{

class EntityBuilder
{
public:
    EntityBuilder(const size_t&& id, const char* name, core::Tag&& tag, core::Layer&& layer);

public:
    EntityBuilder AddTransform();
    EntityBuilder AddCamera();

    /// Add Script

    EntityBuilder AddCameraScript();

    // ��ǰ ��ȯ
    EntityPtr Build();

private:
    EntityPtr _entity;
};

} // namespace game