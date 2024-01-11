/// EntityFactory.h : ��ƼƼ���� �����ϴ� ���丮 Ŭ���� �Դϴ�.
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

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace game
{

class EntityFactory
{
public:    
    EntityPtr CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name);

private:
    EntityPtr CreateCamera(const size_t&& id, const char* name);
};

}