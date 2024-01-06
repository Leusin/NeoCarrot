/// IEventFunction.h: 스크립트 클래스 에서 사용되는
/// 특별한 메서드의 집합을 정의한 추상 클래스 입니다.
///
/// 엔진의 생명주기(life cycle) 이벤트마다
/// 알맞는 메서드가 차례대로 호출됩니다.
///
/// IEventFunction을 상속받은 클래스는
/// 필요한 메서드를 오버라이딩 하여 사용할 수 있습니다.
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
    /// 인스턴스가 생성될 때 호출되는 매서드 입니다.
    ///    사용처: 초기화 작업
    /// </summary>
    virtual void Awake();

    /// <summary>
    /// 인스턴스가 활성화 될 때 호출되는 매서드 입니다.
    ///    사용처: 초기 설정, 다른 오브젝트와의 연동
    /// </summary>
    virtual void Start();

    /// <summary>
    /// 매 프레임마다 호출되는 매서드입니다.
    ///    사용처: 프레임마다 발생하는 로직
    /// </summary>
    virtual void Update();

    /// <summary>
    /// 물리 업데이트 주기마다 호출되는 메서드 입니다.
    ///    사용처: 물리적 계산
    /// </summary>
    virtual void FixedUpdate();

    /// <summary>
    /// 모든 업데이트 주기가 끝난 후 호출되는 메서드 입니다.
    ///    사용처: 다른 Update 메서드들이 끝난 후 실행되는 로직
    /// </summary>
    virtual void LateUpdate();

    /// <summary>
    /// 스크립트가 활성할 때 호출되는 메서드 입니다.
    /// </summary>
    virtual void OnEnable();

    /// <summary>
    /// 스크립트가 비활성할 떄 소출되는 메서드 입니다.
    /// </summary>
    virtual void OnDisable();

    /// <summary>
    /// 스크립트나 게임 오브젝트가 파괴될때 호출되는 메서드 입니다.
    /// </summary>
    virtual void OnDestory();
};

} // namespace core