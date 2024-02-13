/// 2024-01-08

#pragma once

#include "Vector2.h"
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
    void Update(float dt);

    /// <summary>
    /// 현재 마우스 상태 확인
    /// </summary>
    //bool IsButton(mouse::Button button) const;
    //bool IsButtonDown(mouse::Button button) /const;
    //bool IsButtonUp(mouse::Button button) const;

    /// <summary>
    /// 특정 마우스가 눌렸는지 확인
    /// </summary>
    std::optional<mouse::Button> CheckButton() const;

    /// <summary>
    /// 현재 마우스 위치를 가져옴
    /// </summary>
    //math::Vector2<int> GetPosition();

private:

    /// <summary>
    /// 현재 마우스의 위치
    /// </summary>
    static math::Vector2<int> _pos;

    /// <summary>
    /// 마우스가 마지막으로 클릭을 했던 위치
    /// </summary>
    static math::Vector2<int> _lastPos;

    /// <summary>
    /// 마우스 버튼이 눌렸는지 안 눌렸는지에 대한 상태를 보관하는 열거형 배열
    /// 
    /// 템플릿 매개변수는 다음으로 이루어져 있다.
    ///    마우스 버튼 열거형 / 불리언 / 마우스 버튼 수
    /// </summary>
    static EnumArray<mouse::Button, bool, static_cast<unsigned int>(mouse::Button::BUTTON_COUNT)> _mouseMap;
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