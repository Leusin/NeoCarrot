#pragma once
#include "EnumArray.h"
#include "KeyboardEnum.h"
#include <optional>

namespace game
{

class Keyboard
{
private:
    /// <summary>
    /// Ű�� ���¸� �ֱ������� Ȯ��
    /// </summary>
    void Process(float dt);

    /// <summary>
    /// Ư�� Ű�� ���ȴ��� Ȯ��
    /// </summary>
    /// <returns></returns>
    std::optional<keyboard::Key> CheckKeys();

    /// <summary>
    /// Ư�� Ű�� �����ִ��� Ȯ��
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    bool IsKeyPressed(keyboard::Key key);

    /// <summary>
    /// ���� Ű�� �����ִ��� Ȯ��
    /// </summary>
    bool IsKeyDown() const;

    /// <summary>
    /// ���� Ű�� ������ �ִ��� Ȯ��
    /// </summary>
    bool IsKeyUp() const;

    //
    // ���� Ű
    //

    bool DownAlt();
    bool DownControl();
    bool DownShift();
    bool DownSystem();

private:
    /// <summary>
    /// Ű�� ���� ��������
    /// </summary>
    bool _isKeyDown{false};

    /// <summary>
    /// </summary>
    bool _isKeyUp{true};

    /// <summary>
    /// Ű�� ���ȴ��� �� ���ȴ����� ���� ���¸� �����ϴ� ������ �迭
    /// </summary>
    EnumArray<keyboard::Key, bool, static_cast<unsigned int>(keyboard::Key::KEY_COUNT)> _keyMap{};
};

} // namespace game