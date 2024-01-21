#include "IEventFunction.h"

#ifdef CORE_Test
#include <iostream>
#endif // CORE_Test

namespace core
{
//////////////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
inline Entity<Tag, Layer>::Entity(const  size_t&& id, const char* name, Tag&& tag, Layer&& layer) :
Object<Tag, Layer>(std::forward<const size_t>(id), name, std::forward<Tag>(tag), std::forward<Layer>(layer))
{
    // TEST
#ifdef CORE_Test
    printf("\tEntity Construct\n");
#endif // CORE_Test
}

//////////////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
template <typename T, typename... Args>
inline void Entity<Tag, Layer >::AddComponent(Args&&... args)
{
#ifdef CORE_Test
    printf("\tEntity AddComponent Called...\n");
#endif // CORE_Test

    _componentList.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
}

//////////////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
template <typename T>
inline T* Entity<Tag, Layer>::GetComponent()
{
    for (auto& component : _componentList)
    {
        //if (std::is_same<decltype(component), T>::value)
        auto com = dynamic_cast<T*>(component.get());
        if (com) return com;
    }

    return nullptr; // 찾지 못한 경우 nullptr 반환
}

//////////////////////////////////////////////////////////////////////
template <typename Tag, typename Layer>
inline core::Entity<Tag, Layer>::~Entity()
{
#ifdef CORE_Test
    printf("\tEntity Distory\n");
#endif // CORE_Test
}

template <typename Tag, typename Layer>
inline void Entity<Tag, Layer>::Awake()
{
    for (auto& e : _componentList)
        e->Awake();
}

template <typename Tag, typename Layer>
inline void Entity<Tag, Layer>::Start()
{
    for (auto& e : _componentList)
        e->Start();
}

template <typename Tag, typename Layer>
inline void Entity<Tag, Layer>::Update(float dt)
{
    for (auto& e : _componentList)
        e->Update(dt);
}

template <typename Tag, typename Layer>
inline void Entity<Tag, Layer>::FixedUpdate(float dt)
{
    for (auto& e : _componentList)
        e->FixedUpdate(dt);
}

template <typename Tag, typename Layer>
inline void Entity<Tag, Layer>::LateUpdate(float dt)
{
    for (auto& e : _componentList)
        e->LateUpdate(dt);
}

template <typename Tag, typename Layer>
inline void Entity<Tag, Layer>::OnEnable()
{
    for (auto& e : _componentList)
        e->OnDestroy();
}

template <typename Tag, typename Layer>
inline void Entity<Tag, Layer>::OnDisable()
{
    for (auto& e : _componentList)
        e->OnDisable();
}

template <typename Tag, typename Layer>
inline void Entity<Tag, Layer>::OnDestroy()
{
    for (auto& e : _componentList)
        e->OnDestroy();
}
} // namespace core