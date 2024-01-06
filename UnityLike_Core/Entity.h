/// Entity.h : ���� �������� ��� ��ü(entity)�� ��Ÿ���� �����Դϴ�.
/// Entity�� ������ ���� ���(component)�� ���� �ð���, ������, ������ Ư���� �����ϴ�.
///
/// Entity�� �ϳ� �̻��� Component �ɹ��μ� ��������
/// Component �� �����ϴ� ������ �����ϴ�.
///
/// 2024-01-06


#pragma once

#include "Object.h"
#include "IEventFunction.h"

#include <string>


namespace core
{
class IComponent;

template <typename Tag, typename Layer, typename Component>
class Entity : public Object<Tag, Layer>, public IEventFunction
{
public:
    Entity(int&& id, const char* name, Tag&& tag, Layer&& layer);
    ~Entity();

public:
    /// <summary>
    /// ���ڹ��� ������Ʈ Ÿ�Կ� �ش��ϴ� ������Ʈ�� ��ȯ�մϴ�.
    /// 
    /// TODO
    ///    �׸��� ���� �ش� ������Ʈ�� ���ٸ� ��� �ؾ� �� �� �����غ���
    /// 
    /// </summary>
    //virtual IComponent* GetComponent(Component&& compoentType);

    /// <summary>
    /// ������Ʈ�� �����ɴϴ�
    /// </summary>
    //virtual void AddComponent(IComponent* component);
};

} // namespace core

#include "Entity.inl"