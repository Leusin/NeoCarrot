/// TimeManager.h: ������ ����Ǵ� ������ �ð��� �����ϰ� �����ϴ� Ŭ���� �Դϴ�.
///
/// 2024-01-07

#pragma once

class TimeManager
{
public:
    TimeManager();

    /// <summary>
    /// �� ��� �ð��� ��ȯ�մϴ�.
    /// ���α׷��� �� ���۵� �� ���� �� ��� �ð��� ��ȯ�մϴ�.
    /// �̴� ������ ���۵� ������ ��ü ��� �ð��� �ǹ��ϱ⵵ �մϴ�.
    /// </summary>
    /// <returns>���� �ð�(�� ����)</returns>
    float TotalTime() const;

    /// <summary>
    /// �� ������ ���� ��� �ð��� ��Ÿ���ϴ�. 
    /// ���� �ùķ��̼�, �ִϸ��̼�, �̺�Ʈ ó�� ��� ���Ǹ�, 
    /// ������ ���� �ð� ������ �߿��� ��쿡 Ȱ��˴ϴ�.
    /// </summary>
    /// <returns>������ ���� �ð� ������ ��Ÿ Ÿ��(�� ����)</returns>
    float DeltaTime() const;

    /// <summary>
    /// Ÿ�̸ӳ� �ð� ���� ���¸� �ʱ�ȭ�մϴ�.
    /// ���α׷����� �ʱ� ���·� �ǵ������� �� �� ���˴ϴ�.
    /// �޽��� ���� ������ ȣ���ؾ� �մϴ�.
    /// </summary>
    void Reset();

    /// <summary>
    /// �ð� ������ �����մϴ�.
    /// </summary>
    void Start(); // Ÿ�̸� ���� �Ǵ� �簳 �� ȣ��

    /// <summary>
    /// �Ͻ����� ������ �� ȣ��Ǿ� �ð� ������ �����մϴ�. 
    /// </summary>
    void Stop();  // �Ͻ����� �� ȣ��

    /// <summary>
    /// ������ ���� �ð��� �����մϴ�.
    /// </summary>
    void Tick();  // �� �����Ӹ��� ȣ��

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
