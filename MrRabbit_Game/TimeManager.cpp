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

    // �ߴ� ���¿��� Ÿ�̸Ӹ��ٽ� �簳�ϴ� ���
    if (_stopped)
    {
        // �Ͻ����� �ð�������
        _pausedTime += (startTime - _stopTime);

        // ���� �ð����� ����
        _prevTime = startTime;
        _stopTime = 0;
        _stopped  = false;
    }
}

void TimeManager::Stop()
{
    // �̹� ���� ��������
    if (!_stopped)
    {
        __int64 currTime;
        QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

        // �ߴ� �ð�(�Ͻ� ������ ������ �ð�)�� �����ϰ� �÷��׸� ����
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

    // �̹� �������� ��´� .
    __int64 currTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
    _currTime = currTime;

    // ���� �����Ӱ� ���� �������� ���� ����
    _deltaTime = (_currTime - _prevTime) * _secondsPerCount;

    // ���� �������� �غ�
    _prevTime = _currTime;

    // ��Ÿ Ÿ���� ������ �ƴϾ� ��
    if (_deltaTime < 0.0)
    {
        _deltaTime = 0.0;
    }
}

void TimeManager::CalculateFrameStats()
{
    _frameCount++;

    // 1�� ���� ��� ������ �� ���
    if (TotalTime() - _timeElapsed >= 1.0f)
    {
        _fps = static_cast<float>(_frameCount);
        _mspf = 1000.0f / _fps;

        // ���� ��� ����� ���� �ʱ�ȭ
        _frameCount = 0;
        _timeElapsed += 1.0f;
    }
}

float TimeManager::FPS()
{
    return _fps;
}

} // namespace game