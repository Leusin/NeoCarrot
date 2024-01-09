#ifdef CORE_Test
#include <iostream>
#endif // CORE_Test

namespace core
{
////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
inline Entity<Tag, Layer>::Entity(const  size_t&& id, const char* name, Tag&& tag, Layer&& layer) :
Object<Tag, Layer>(std::forward<const size_t>(id), name, std::forward<Tag>(tag), std::forward<Layer>(layer))
{
    // TEST
#ifdef CORE_Test
    printf("\tEntity Construct\n");
#endif // CORE_Test
}

////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
inline core::Entity<Tag, Layer>::~Entity()
{
#ifdef CORE_Test
    printf("\tEntity Distory\n");
#endif // CORE_Test
}

////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
template <typename T, typename... Args>
inline void Entity<Tag, Layer >::AddComponent(Args&&... args)
{
#ifdef CORE_Test
    printf("\tEntity AddComponent Called...\n");
#endif // CORE_Test

    _componentList.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
}

////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
template <typename T>
inline T* Entity<Tag, Layer>::GetComponent()
{
    for (auto& component : _componentList)
    {
        if (std::is_same<decltype(component), T>::value)
        {
            return dynamic_cast<T*>(component.get());
        }
    }

    return nullptr; // 찾지 못한 경우 nullptr 반환
}

} // namespace core