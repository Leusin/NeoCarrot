/// IEventFunction.h: ��ũ��Ʈ Ŭ���� ���� ���Ǵ�
/// Ư���� �޼����� ������ ������ �߻� Ŭ���� �Դϴ�.
///
/// ������ �����ֱ�(life cycle) �̺�Ʈ����
/// �˸´� �޼��尡 ���ʴ�� ȣ��˴ϴ�.
///
/// IEventFunction�� ��ӹ��� Ŭ������
/// �ʿ��� �޼��带 �������̵� �Ͽ� ����� �� �ֽ��ϴ�.
///
/// 2024-01-06


#pragma once

namespace core
{

class IEventFunction
{
public:
    virtual ~IEventFunction(){};

public:
    /// <summary>
    /// �ν��Ͻ��� ������ �� ȣ��Ǵ� �ż��� �Դϴ�.
    ///    ���ó: �ʱ�ȭ �۾�
    /// </summary>
    virtual void Awake();

    /// <summary>
    /// �ν��Ͻ��� Ȱ��ȭ �� �� ȣ��Ǵ� �ż��� �Դϴ�.
    ///    ���ó: �ʱ� ����, �ٸ� ������Ʈ���� ����
    /// </summary>
    virtual void Start();

    /// <summary>
    /// �� �����Ӹ��� ȣ��Ǵ� �ż����Դϴ�.
    ///    ���ó: �����Ӹ��� �߻��ϴ� ����
    /// </summary>
    virtual void Update();

    /// <summary>
    /// ���� ������Ʈ �ֱ⸶�� ȣ��Ǵ� �޼��� �Դϴ�.
    ///    ���ó: ������ ���
    /// </summary>
    virtual void FixedUpdate();

    /// <summary>
    /// ��� ������Ʈ �ֱⰡ ���� �� ȣ��Ǵ� �޼��� �Դϴ�.
    ///    ���ó: �ٸ� Update �޼������ ���� �� ����Ǵ� ����
    /// </summary>
    virtual void LateUpdate();

    /// <summary>
    /// ��ũ��Ʈ�� Ȱ���� �� ȣ��Ǵ� �޼��� �Դϴ�.
    /// </summary>
    virtual void OnEnable();

    /// <summary>
    /// ��ũ��Ʈ�� ��Ȱ���� �� ����Ǵ� �޼��� �Դϴ�.
    /// </summary>
    virtual void OnDisable();

    /// <summary>
    /// ��ũ��Ʈ�� ���� ������Ʈ�� �ı��ɶ� ȣ��Ǵ� �޼��� �Դϴ�.
    /// </summary>
    virtual void OnDestory();
};

} // namespace core