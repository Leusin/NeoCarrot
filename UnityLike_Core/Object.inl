#ifdef CORE_Test
#include <iostream>
#endif // CORE_Test

namespace core
{
////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
inline Object<Tag, Layer>::Object(const size_t&& id, std::string&& name, Tag&& tag, Layer&& layer) :
_id(std::forward<const size_t>(id)),
_name(std::forward<std::string>(name)),
_tag(std::forward<Tag>(tag)),
_layer(std::forward<Layer>(layer))
{
#ifdef CORE_Test
    printf("Object Constructed ( %zu %s )\n", id, this->_name.c_str());
#endif // CORE_Test
}

////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
inline Object<Tag, Layer>::~Object()
{
#ifdef CORE_Test
    printf("Object Destoryed ( %zd %s )\n", _id, _name.c_str());
#endif // CORE_Test
}

////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
inline void Object<Tag, Layer>::Destroy()
{
#ifdef CORE_Test
    printf("Object Destory Called...\n");
#endif // CORE_Test
    // 스마트 포인터를 통해 자동으로 객체를 삭제
    std::shared_ptr<Object<Tag, Layer>> selfSharedPtr = this->shared_from_this();
}

} // namespace core
