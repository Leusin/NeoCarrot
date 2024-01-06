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

template <typename enumTagType, typename enumLayer>
class Object : public std::enable_shared_from_this<Object<enumTagType, enumLayer>>
{
/// <summary>
/// Object Ŭ������ ���� �������� ���ϰ� �ϵ��η�
/// protected ���� ������ ���� ����
/// </summary>
protected:
    Object(int&& id, std::string&& name, enumTagType&& type, enumLayer&& layer);

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
    enumTagType tag;
    enumLayer   layer;

private:
    /// <summary>
    /// ��ü�� �ĺ� �� �˻��� ���� ������.
    /// </summary>
    int         id;
    std::string name;
};

template <typename enumTagType, typename enumLayer>
inline Object<enumTagType, enumLayer>::Object(int&& id, std::string&& name, enumTagType&& type, enumLayer&& layer) :
id(id),
name(std::move(name)),
tag(type),
layer(layer)
{
    // TEST
#ifdef _DEBUG
    printf("Object class\n\t( %d ) %s Object Constructed\n", id, name.c_str());
#endif // DEBUG
}

template <typename enumTagType, typename enumLayer>
inline Object<enumTagType, enumLayer>::~Object()
{
}

template <typename enumTagType, typename enumLayer>
inline void Object<enumTagType, enumLayer>::Destroy()
{
    // TEST
#ifdef _DEBUG
    printf("Object class\n\t( %d ) %s Object Destory\n", id, name.c_str());
#endif // DEBUG

    // ����Ʈ �����͸� ���� �ڵ����� ��ü�� ����
    std::shared_ptr<Object<enumTagType, enumLayer>> selfSharedPtr = this->shared_from_this();
}

} // namespace core