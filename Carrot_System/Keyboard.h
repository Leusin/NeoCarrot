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
    /// 키의 상태를 주기적으로 확인
    /// </summary>
    void Process(float dt);

    /// <summary>
    /// 특정 키가 눌렸는지 확인
    /// </summary>
    /// <returns></returns>
    std::optional<keyboard::Key> CheckKeys();

    /// <summary>
    /// 특정 키가 눌려있는지 확인
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    bool IsKeyPressed(keyboard::Key key);

    /// <summary>
    /// 현재 키가 눌려있는지 확인
    /// </summary>
    bool IsKeyDown() const;

    /// <summary>
    /// 현재 키가 떼어져 있는지 확인
    /// </summary>
    bool IsKeyUp() const;

    //
    // 보조 키
    //

    bool DownAlt();
    bool DownControl();
    bool DownShift();
    bool DownSystem();

private:
    /// <summary>
    /// 키가 눌린 상태인지
    /// </summary>
    bool _isKeyDown{false};

    /// <summary>
    /// </summary>
    bool _isKeyUp{true};

    /// <summary>
    /// 키가 눌렸는지 안 눌렸는지에 대한 상태를 보관하는 열거형 배열
    /// </summary>
    EnumArray<keyboard::Key, bool, static_cast<unsigned int>(keyboard::Key::KEY_COUNT)> _keyMap{};
};

} // namespace game