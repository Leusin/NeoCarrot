/// IEntity.h : 추상 클래스 입니다. Entity 가 꼭 구현해야할 메서드를 정의합니다.
///
/// Entity는 Component 목록을 맴버로서 가지지며
/// Component 를 관리하는 역할을 맏습니다.
/// 따라서 Entity 의 메서드는 주로 Component 를 관리합니다.
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
    /// 상속을 위한 가상 소멸자.
    /// </summary>
    virtual ~IEntity(){};

public:
    /// <summary>
    /// 인자받은 컴포넌트 타입에 해당하는 컴포넌트를 반환합니다.
    /// 
    /// TODO
    ///    그리고 만을 해당 컴포넌트가 없다면 어떻게 해야 할 지 생각해보기
    /// 
    /// </summary>
    virtual IComponent* GetComponent(/*어떤 컴포넌트를 가져올지 확인해야 한다.*/) abstract;

    /// <summary>
    /// 컴포넌트를 가져옵니다
    /// </summary>
    virtual void        AddComponent(IComponent* component) abstract;
};

} // namespace game