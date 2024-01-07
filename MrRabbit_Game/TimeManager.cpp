#include "TimeManager.h"

#include <windows.h>

namespace game
{

imeManager::TimeManager()
{
    __int64 countsPerSec;
    QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
    _secondsPerCount = 1.0 / (double)countsPerSec;
}

float TimeManager::TotalTime() const
{
    if (_stopped)
    {
        return static_cast<float>(((_stopTime - _pausedTime) - _baseTime) * _secondsPerCount);
    }

    return static_cast<float>(((_currTime - _pausedTime) - _baseTime) * _secondsPerCount);
}

float TimeManager::DeltaTime() const
{
    return static_cast<float>(_deltaTime);
}

void TimeManager::Reset()
{
    __int64 currTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

    _baseTime = currTime;
    _prevTime = currTime;
    _stopTime = 0;
    _stopped  = false;
}

void TimeManager::Start()
{
    __int64 startTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

    // 중단 상태에서 타이머를다시 재개하는 경우
    if (_stopped)
    {
        // 일시정지 시간을누적
        _pausedTime += (startTime - _stopTime);

        // 현재 시간으로 설정
        _prevTime = startTime;
        _stopTime = 0;
        _stopped  = false;
    }
}

void TimeManager::Stop()
{
    // 이미 정지 상태인자
    if (!_stopped)
    {
        __int64 currTime;
        QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

        // 중단 시간(일시 정지된 시점의 시간)을 저장하고 플래그를 설정
        _stopTime = currTime;
        _stopped  = true;
    }
}

void TimeManager::Tick()
{
    if (_stopped)
    {
        _deltaTime = 0.0;
        return;
    }

    // 이번 프레임을 얻는다 .
    __int64 currTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
    _currTime = currTime;

    // 지금 프레임과 이전 프레임의 차를 구함
    _deltaTime = (_currTime - _prevTime) * _secondsPerCount;

    // 다음 프레임을 준비
    _prevTime = _currTime;

    // 델타 타임은 음수가 아니야 함
    if (_deltaTime < 0.0)
    {
        _deltaTime = 0.0;
    }
}

void TimeManager::CalculateFrameStats()
{
    _frameCount++;

    // 1초 동안 평균 프레임 수 계산
    if (TotalTime() - _timeElapsed >= 1.0f)
    {
        _fps = static_cast<float>(_frameCount);
        _mspf = 1000.0f / _fps;

        // 다음 평균 계산을 위한 초기화
        _frameCount = 0;
        _timeElapsed += 1.0f;
    }
}

float TimeManager::FPS()
{
    return _fps;
}

} // namespace game