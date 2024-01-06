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


namespace core
{
class IComponent;

template <typename enumTag, typename enumLayer, typename enumComponent>
class Entity : public Object<enumTag, enumLayer>, public IEventFunction
{
public:
    //Entity();
    ~Entity(){};

public:
    /// <summary>
    /// ���ڹ��� ������Ʈ Ÿ�Կ� �ش��ϴ� ������Ʈ�� ��ȯ�մϴ�.
    /// 
    /// TODO
    ///    �׸��� ���� �ش� ������Ʈ�� ���ٸ� ��� �ؾ� �� �� �����غ���
    /// 
    /// </summary>
    virtual IComponent* GetComponent(enumComponent&& compoentType){};

    /// <summary>
    /// ������Ʈ�� �����ɴϴ�
    /// </summary>
    virtual void AddComponent(IComponent* component){};
};

} // namespace game