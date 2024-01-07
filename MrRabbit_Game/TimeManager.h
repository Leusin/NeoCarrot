/// TimeManager.h
///
/// 2024-01-07

#pragma once

class TimeManager
{
public:
    float TotalTime() const; // �� ����
    float DeltaTime() const; // �� ����

    void Reset(); // �޽��� ���� ������ ȣ��
    void Start(); // Ÿ�̸� ���� �Ǵ� �簳 �� ȣ��
    void Stop();  // �Ͻ����� �� ȣ��
    void Tick();  // �� �����Ӹ��� ȣ��

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
