/// TimeManager.h: 게임이 실행되는 동안의 시간을 추적하고 관리하는 클레스 입니다.
///
/// 2024-01-07

#pragma once

class TimeManager
{
public:
    TimeManager();

    /// <summary>
    /// 총 경과 시간을 반환합니다.
    /// 프로그램이 이 시작된 후 지난 총 경과 시간을 반환합니다.
    /// 이는 게임이 시작된 이후의 전체 경과 시간을 의미하기도 합니다.
    /// </summary>
    /// <returns>실행 시간(초 단위)</returns>
    float TotalTime() const;

    /// <summary>
    /// 두 프레임 간의 경과 시간을 나타냅니다. 
    /// 물리 시뮬레이션, 애니메이션, 이벤트 처리 등에서 사용되며, 
    /// 프레임 간의 시간 간격이 중요한 경우에 활용됩니다.
    /// </summary>
    /// <returns>프레임 간의 시간 간격인 델타 타임(초 단위)</returns>
    float DeltaTime() const;

    /// <summary>
    /// 타이머나 시간 관리 상태를 초기화합니다.
    /// 프로그램의을 초기 상태로 되돌리고자 할 때 사용됩니다.
    /// 메시지 루프 이전에 호출해야 합니다.
    /// </summary>
    void Reset();

    /// <summary>
    /// 시간 측정을 시작합니다.
    /// </summary>
    void Start(); // 타이머 시작 또는 재개 시 호출

    /// <summary>
    /// 일시정지 상태일 때 호출되어 시간 측정을 중지합니다. 
    /// </summary>
    void Stop();  // 일시정지 시 호출

    /// <summary>
    /// 프레임 간의 시간을 갱신합니다.
    /// </summary>
    void Tick();  // 매 프레임마다 호출

private:
    double _secondsPerCount{0.0};
    double _deltaTime{-1.0};

    __int64 _baseTime{0};
    __int64 _pausedTime{0};
    __int64 _stopTime{0};
    __int64 _prevTime{0};
    __int64 _currTime{0};

    bool _stopped{false};
};
