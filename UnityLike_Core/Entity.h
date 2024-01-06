/// Entity.h : ���� �������� ��� ��ü(entity)�� ��Ÿ���� �����Դϴ�.
/// Entity�� ������ ���� ���(component)�� ���� �ð���, ������, ������ Ư���� �����ϴ�.
///
/// Entity�� �ϳ� �̻��� Component �ɹ��μ� ��������
/// Component �� �����ϴ� ������ �����ϴ�.
///
/// 2024-01-06


#pragma once


namespace game
{
class IComponent;

class Entity
{
public:
    /// <summary>
    /// ����� ���� ���� �Ҹ���.
    /// </summary>
    virtual ~Entity(){};

public:
    /// <summary>
    /// ���ڹ��� ������Ʈ Ÿ�Կ� �ش��ϴ� ������Ʈ�� ��ȯ�մϴ�.
    /// 
    /// TODO
    ///    �׸��� ���� �ش� ������Ʈ�� ���ٸ� ��� �ؾ� �� �� �����غ���
    /// 
    /// </summary>
    virtual IComponent* GetComponent(/*� ������Ʈ�� �������� Ȯ���ؾ� �Ѵ�.*/) abstract;

    /// <summary>
    /// ������Ʈ�� �����ɴϴ�
    /// </summary>
    virtual void        AddComponent(IComponent* component) abstract;

};

} // namespace game