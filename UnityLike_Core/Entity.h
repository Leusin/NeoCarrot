/// IEntity.h : �߻� Ŭ���� �Դϴ�. Entity �� �� �����ؾ��� �޼��带 �����մϴ�.
///
/// Entity�� Component ����� �ɹ��μ� ��������
/// Component �� �����ϴ� ������ �����ϴ�.
/// ���� Entity �� �޼���� �ַ� Component �� �����մϴ�.
///
/// 2024-01-06

#pragma once

namespace game
{
class IComponent;

class IEntity
{
public:
    /// <summary>
    /// ����� ���� ���� �Ҹ���.
    /// </summary>
    virtual ~IEntity(){};

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