/// 2024-01-08

#pragma once

#include "../Bunny_Math/Vector2.h"
#include "EnumArray.h"
#include "MouseEnum.h"

#include <functional>
#include <optional>

namespace game
{

class Mouse
{
public:
    /// <summary>
    /// 마우스의 상태를 주기적으로 확인
    /// </summary>
    void Process(float dt);

    /// <summary>
    /// 특정 마우스가 눌렸는지 확인
    /// </summary>
    std::optional<mouse::Button> CheckButton() const;

    /// <summary>
    /// 특정 마우스 버튼이 눌려있는지 확인
    /// </summary>
    /// <param name="button">확인하려는 마우스 버튼</param>
    /// <returns>참 또는 거짓</returns>
    bool IsButtonPressed(mouse::Button button) const;

    /// <summary>
    /// 현재 마우스 위치를 가져옴
    /// </summary>
    math::Vector2<int> GetPosition();

    /// <summary>
    /// 현재 마우스가 눌려있는지 확인
    /// </summary>
    bool IsMouseDown() const;

    /// <summary>
    /// 현재 마우스가 떼어져 있는지 확인
    /// </summary>
    bool IsMouseUp() const;

private:

    /// <summary>
    /// 마우스 버튼이 눌린 상태인지
    /// </summary>
    bool _isMouseDown{false};

    /// <summary>
    /// 마우스 버튼이 눌리지 않은 상태인지
    /// </summary>
    bool _isMouseUp{true};

    /// <summary>
    /// 현재 마우스의 위치
    /// </summary>
    math::Vector2<int> _mousePos;

    /// <summary>
    /// 마우스가 마지막으로 클릭을 했던 위치
    /// </summary>
    math::Vector2<int> _lastPressedButton;

    /// <summary>
    /// 마우스 버튼이 눌렸는지 안 눌렸는지에 대한 상태를 보관하는 열거형 배열
    /// </summary>
    EnumArray<mouse::Button, bool, static_cast<unsigned int>(mouse::Button::BUTTON_COUNT)> _mouseMap{};
};

} // namespace game

/*
    bool _IsLeftButtonDown;
	bool _IsLeftDragging;
	POINT _MouseNowPos;
	POINT  _DragStartPos;

    /// 키입력 또는 마우스 입력을 받는다
	GetCursorPos(&_MouseNowPos);

	// 마우스 위치를 조절
	RECT rt;
	GetWindowRect(_hWnd, &rt);
	_MouseNowPos.x -= rt.left + 5;
	_MouseNowPos.y -= rt.top + 23;

	/// 마우스 입력 세분화
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (_IsLeftButtonDown == false)
		{
			_DragStartPos = _MouseNowPos;
			_IsLeftDragging = true;
		}
		_IsLeftButtonDown = true;
	}
	else
	{
		if (_IsLeftButtonDown == true)
		{
			AreaSelect(_DragStartPos.x, _DragStartPos.y, _MouseNowPos.x, _MouseNowPos.y);
		}
		_IsLeftButtonDown = false;
		_IsLeftDragging = false;
	}

*/