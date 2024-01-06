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

#ifdef _DEBUG
#include <iostream>
#endif // DEBUG

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
    bool isActive{false};

    /// <summary>
    /// ������Ʈ�� ������ �Ӽ��̳�
    /// ������ �ĺ��ϴµ� ����ϴ� ������.
    /// </summary>
    Tag tag;
    Layer   layer;

private:
    /// <summary>
    /// ��ü�� �ĺ� �� �˻��� ���� ������.
    /// </summary>
    const int         id;
    const std::string name;
};

template <typename Tag, typename Layer>
inline Object<Tag, Layer>::Object(int id, std::string name, Tag type, Layer layer) :
id(id),
name(std::move(name)),
tag(type),
layer(layer)
{
    // TEST
#ifdef _DEBUG
    printf("Object Constructed ( %d %s )\n", id, this->name.c_str());
#endif // DEBUG
}

template <typename Tag, typename Layer>
inline Object<Tag, Layer>::~Object()
{
    // TEST
#ifdef _DEBUG
    printf("Object Destoryed ( %d %s )\n", id, name.c_str());
#endif // DEBUG
}

template <typename Tag, typename Layer>
inline void Object<Tag, Layer>::Destroy()
{
#ifdef _DEBUG
    printf("Object Destory Calld...\n");
#endif // DEBUG
    // ����Ʈ �����͸� ���� �ڵ����� ��ü�� ����
    std::shared_ptr<Object<Tag, Layer>> selfSharedPtr = this->shared_from_this();
}

} // namespace core