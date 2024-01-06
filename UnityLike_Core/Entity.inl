#pragma once

namespace core
{
template <typename enumTag, typename enumLayer, typename enumComponent>
inline Entity<enumTag, enumLayer, enumComponent>::Entity(int&& id, const char*&& name, enumTag&& type, enumLayer&& layer) :
Object(id, name, type, layer)
{
}
} // namespace core