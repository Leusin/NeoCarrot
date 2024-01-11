/// 생성중인 엔티티를 관리하는 빌더 클래스 입니다.
/// 종류에 따라 엔티티가 필요로 하는 컴포넌트를 조립합니다.
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

    // 제품 반환
    EntityPtr Build();

private:
    EntityPtr _entity;
};

} // namespace game