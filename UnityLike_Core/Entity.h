/// Entity.h : ���� �������� ��� ��ü(entity)�� ��Ÿ���� �����Դϴ�.
/// Entity�� ������ ���� ���(component)�� ���� �ð���, ������, ������ Ư���� �����ϴ�.
///
/// Entity�� �ϳ� �̻��� Component �ɹ��μ� ��������
/// Component �� �����ϴ� ������ �����ϴ�.
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
    /// ������Ʈ�� �����ɴϴ�
    /// </summary>
    //template <typename T>
    template <typename T, typename... Args>
    void AddComponent(Args&&... args);

    /// <summary>
    /// ���ڷ� ���� ���� ������Ʈ Ÿ�Կ� �ش��ϴ�
    /// ������Ʈ�� ��ȯ�մϴ�.
    /// </summary>
    template <typename T>
    T* GetComponent();

private:
    std::vector<std::unique_ptr<IComponent>> _componentList;
};

} // namespace core

#include "Entity.inl"