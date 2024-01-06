/// Entity.h : 게임 엔진에서 모든 개체(entity)를 나타내는 단위입니다.
/// Entity이 가지는 구성 요소(component)를 통해 시각적, 물리적, 동작적 특성을 갖습니다.
///
/// Entity는 하나 이상의 Component 맴버로서 가지지며
/// Component 를 관리하는 역할을 맏습니다.
///
/// 2024-01-06


#pragma once

#include "IEventFunction.h"
#include "Object.h"
#include "IComponent.h"

#include <memory>
#include <vector>


namespace core
{

template <typename Tag, typename Layer/*, typename ComponentT*/>
class Entity : public Object<Tag, Layer>, public IEventFunction
{
public:
    Entity(int&& id, const char* name, Tag&& tag, Layer&& layer);
    ~Entity();

public:
    /// <summary>
    /// 컴포넌트를 가져옵니다
    /// </summary>
    //template <typename T>
    template <typename T, typename... Args>
    void AddComponent(Args&&... args);

    /// <summary>
    /// 인자로 전달 받은 컴포넌트 타입에 해당하는
    /// 컴포넌트를 반환합니다.
    /// </summary>
    template <typename T>
    T* GetComponent();

private:
    std::vector<std::unique_ptr<IComponent>> _componentList;
};

} // namespace core

#include "Entity.inl"