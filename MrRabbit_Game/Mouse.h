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
    /// ���콺�� ���¸� �ֱ������� Ȯ��
    /// </summary>
    void Process(float dt);

    /// <summary>
    /// Ư�� ���콺�� ���ȴ��� Ȯ��
    /// </summary>
    std::optional<mouse::Button> CheckButton() const;

    /// <summary>
    /// Ư�� ���콺 ��ư�� �����ִ��� Ȯ��
    /// </summary>
    /// <param name="button">Ȯ���Ϸ��� ���콺 ��ư</param>
    /// <returns>�� �Ǵ� ����</returns>
    bool IsButtonPressed(mouse::Button button) const;

    /// <summary>
    /// ���� ���콺 ��ġ�� ������
    /// </summary>
    math::Vector2<int> GetPosition();

    /// <summary>
    /// ���� ���콺�� �����ִ��� Ȯ��
    /// </summary>
    bool IsMouseDown() const;

    /// <summary>
    /// ���� ���콺�� ������ �ִ��� Ȯ��
    /// </summary>
    bool IsMouseUp() const;

private:

    /// <summary>
    /// ���콺 ��ư�� ���� ��������
    /// </summary>
    bool _isMouseDown{false};

    /// <summary>
    /// ���콺 ��ư�� ������ ���� ��������
    /// </summary>
    bool _isMouseUp{true};

    /// <summary>
    /// ���� ���콺�� ��ġ
    /// </summary>
    math::Vector2<int> _mousePos;

    /// <summary>
    /// ���콺�� ���������� Ŭ���� �ߴ� ��ġ
    /// </summary>
    math::Vector2<int> _lastPressedButton;

    /// <summary>
    /// ���콺 ��ư�� ���ȴ��� �� ���ȴ����� ���� ���¸� �����ϴ� ������ �迭
    /// </summary>
    EnumArray<mouse::Button, bool, static_cast<unsigned int>(mouse::Button::BUTTON_COUNT)> _mouseMap{};
};

} // namespace game

/*
    bool _IsLeftButtonDown;
	bool _IsLeftDragging;
	POINT _MouseNowPos;
	POINT  _DragStartPos;

    /// Ű�Է� �Ǵ� ���콺 �Է��� �޴´�
	GetCursorPos(&_MouseNowPos);

	// ���콺 ��ġ�� ����
	RECT rt;
	GetWindowRect(_hWnd, &rt);
	_MouseNowPos.x -= rt.left + 5;
	_MouseNowPos.y -= rt.top + 23;

	/// ���콺 �Է� ����ȭ
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