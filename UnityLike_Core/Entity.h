/// Entity.h : ���� �������� ��� ��ü(entity)�� ��Ÿ���� �����Դϴ�.
/// Entity�� ������ ���� ���(component)�� ���� �ð���, ������, ������ Ư���� �����ϴ�.
///
/// Entity�� �ϳ� �̻��� Component �ɹ��μ� ��������
/// Component �� �����ϴ� ������ �����ϴ�.
///
/// 2024-01-06


#pragma once

#include "IComponent.h"
#include "Object.h"

#include <memory>
#include <vector>


namespace core
{

class IComponent;

template<typename Tag, typename Layer>
class Entity: public Object<Tag, Layer>, public IEventFunction
{
public:
    Entity(const size_t&& id, const char* name, Tag&& tag, Layer&& layer);
    ~Entity();

public:
    /// <summary>
    /// ������Ʈ�� �����ɴϴ�
    /// </summary>
    template<typename T, typename... Args>
    void AddComponent(Args&&... args);

    /// <summary>
    /// ���ڷ� ���� ���� ������Ʈ Ÿ�Կ� �ش��ϴ�
    /// ������Ʈ�� ��ȯ�մϴ�.
    /// </summary>
    template<typename T>
    T* GetComponent();

    //
    // IEventFunction
    //

    void Awake() override;
    void Start() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void LateUpdate(float dt) override;

    void OnEnable() override;
    void OnDisable() override;
    void OnDestroy() override;

private:
    std::vector<std::unique_ptr<IComponent>> _componentList;
};

} // namespace core

#include "Entity.inl"