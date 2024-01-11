#pragma once

#include "IFactory.h"

namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{

class ModelFactory : public core::IFactory
{
public:
    ModelFactory();

    EntityPtr CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name);

private:
    EntityPtr CreateBox(const size_t&& id, const char* name);

    /// TODO
    ///    여기에 리소스 메니저
    /// 
};

} // namespace graphics