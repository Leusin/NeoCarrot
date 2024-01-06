/// Entity.h : 게임 엔진에서 모든 개체(entity)를 나타내는 단위입니다.
/// Entity이 가지는 구성 요소(component)를 통해 시각적, 물리적, 동작적 특성을 갖습니다.
///
/// Entity는 하나 이상의 Component 맴버로서 가지지며
/// Component 를 관리하는 역할을 맏습니다.
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
    /// 상속을 위한 가상 소멸자.
    /// </summary>
    virtual ~Entity(){};

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