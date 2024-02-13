/// System.cpp : ������ �帧�� ���� �� �����մϴ�.
/// ��κ� �Ŵ��� Ŭ�������� ���⿡ �ֽ��ϴ�.
///
/// 2023-12-22


#pragma once

#include "Input.h"
#include "WindowInfo.h"
#include "../Clover_Graphics/Renderor.h"

#include <memory>
#include <windows.h>

namespace game
{

class System
{
public:
    System(data::WindowInfo* winInfo);
    ~System();

    void Initialize();
    void Process();
    void Finalize();

    LRESULT MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    // ������ ����
    data::WindowInfo* _windowInfo{ nullptr };

    // �׷��� ����
    std::unique_ptr<graphics::D3D11Renderor> _renderer{ nullptr };

    std::unique_ptr<Input> _input{ nullptr };

    // std::unique_ptr<data::ForGraphics>  _graphicsInfo;
    // std::unique_ptr<SceneManager> _sceneManager;
    // std::unique_ptr<TimeManager>  _timeManager;
};

} // namespace game