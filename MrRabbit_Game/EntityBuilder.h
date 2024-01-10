/// 종류에 따라 엔티티가 필요로 하는 컴포넌트를 조립해 주는
/// 빌더 클래래스 입니다.
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

    // 제품 반환
    EntityPtr     Build();

private:
    EntityPtr _entity;
};

} // namespace game