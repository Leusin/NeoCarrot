#pragma once

#ifdef _DEBUG
#include <iostream>
#endif // DEBUG

namespace core
{
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
}
