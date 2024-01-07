/// TimeManager.h
///
/// 2024-01-07

#pragma once

class TimeManager
{
public:
    float TotalTime() const; // 초 단위
    float DeltaTime() const; // 초 단위

    void Reset(); // 메시지 루프 이전에 호출
    void Start(); // 타이머 시작 또는 재개 시 호출
    void Stop();  // 일시정지 시 호출
    void Tick();  // 매 프레임마다 호출

private:
    double _secondsPerCount;
    double _deltaTime;

    __int64 _baseTime;
    __int64 _pausedTime;
    __int64 _stopTime;
    __int64 _prevTime;
    __int64 _currTime;

    bool _stopped;
};
