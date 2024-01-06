/// Object.h : ���� �������� ��� ��ü�� �⺻ Ŭ���� �Դϴ�.
/// �̸� ���� �������� ����� ����� ����� �� �ֽ��ϴ�.
///
/// Object Ŭ������ �ֿ� ���
///    - �ĺ��ڿ� �̸�
///    - ���� ��ü�� Ȱ�� ����
///    - �±�� ���̾�
///    - Destory �� Instantiate
///
/// 2024-01-06


#pragma once

#include <memory>
#include <string>

namespace core
{

template <typename Tag, typename Layer>
class Object : public std::enable_shared_from_this<Object<Tag, Layer>>
{
    /// <summary>
    /// Object Ŭ������ ���� �������� ���ϰ� �ϵ���
    /// protected ���� ������ ���� ����
    /// </summary>

protected:
    Object(int id, std::string name, Tag tag, Layer layer);

public:
    /// <summary>
    /// ����� ���� ���� �Ҹ���.
    /// </summary>
    ~Object();

public:
    /// <summary>
    /// ��ü�� �Ҹ��Ű�µ� ���˴ϴ�.
    ///    ���ó: ���ʿ��� ��ü ����, �� ��ȯ�� �������� ��ü ����
    /// </summary>
    virtual void Destroy();

    /// <summary>
    /// ������(Prefab) ������� ���ο� ���� ������Ʈ�� �����մϴ�.
    ///
    /// TODO
    ///    �ش� �Լ��� ��� �����غ����� �� �� ���
    ///
    /// </summary>
    //virtual void Instantiate();

public:
    //constexpr int&         GetId() const;
    //constexpr std::string& GetName() const;

public:
    /// <summary>
    /// ��ü�� Ȱ�� ����.
    /// </summary>
    bool _isActive{false};

    /// <summary>
    /// ������Ʈ�� ������ �Ӽ��̳�
    /// ������ �ĺ��ϴµ� ����ϴ� ������.
    /// </summary>
    Tag   _tag;
    Layer _layer;

private:
    /// <summary>
    /// ��ü�� �ĺ� �� �˻��� ���� ������.
    /// </summary>
    const int         _id;
    const std::string _name;
};

} // namespace core

#include "Object.inl"