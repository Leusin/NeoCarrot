#include "Application.h"

#include "resource.h"

namespace
{
// ���� â���� Window �޽����� �����ϴµ� ����Ѵ�.
Application* app{ nullptr };

} // namespace

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return app->GetWinMssageProc(hwnd, msg, wParam, lParam);
}

Application::Application(const HINSTANCE& hIns)
{
    app = this;

    _winInfo.hInstance = hIns;

    InitalizeMainWindow();

    _gameSystem = std::make_unique<game::System>(&_winInfo);

}

Application::~Application()
{
    app = nullptr;
}

void Application::Initialize()
{
    _gameSystem->Initialize();
}

void Application::Process()
{
    _gameSystem->Process();
}

void Application::Finalize()
{
    _gameSystem->Finalize();
}

LRESULT CALLBACK
    Application::GetWinMssageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return _gameSystem->MessageProc(hwnd, msg, wParam, lParam);
}

void Application::InitalizeMainWindow()
{
    WNDCLASS windowClass = { 0, };

    windowClass.style       = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = MainWndProc;        // ������ ���ν���
    windowClass.cbClsExtra  = 0;                  // Ŭ���� ���� �޸�
    windowClass.cbWndExtra  = 0;                  // ������ ���� �޸�
    windowClass.hInstance   = _winInfo.hInstance; // �ν��Ͻ�
    windowClass.hIcon = LoadIcon(_winInfo.hInstance, MAKEINTRESOURCE(IDI_ICON1)); // ������
    windowClass.hCursor = LoadCursor(0, IDC_ARROW);                 // Ŀ��
    windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // ��׶���
    windowClass.lpszMenuName  = 0;                         // �޴� �̸�
    windowClass.lpszClassName = _winInfo.mainWndclassName; // Ŭ���� �̸�

    if (!RegisterClass(&windowClass))
    {
        MessageBox(0, L"RegisterClass ȣ�� ����.", 0, 0);
        return;
    }

    RECT cilentPositionAndSize = { _winInfo.clienLeft,
                                   _winInfo.clienTop,
                                   _winInfo.clientWidth,
                                   _winInfo.clientHeight };

    AdjustWindowRect(&cilentPositionAndSize, WS_OVERLAPPEDWINDOW, false);
    int width  = cilentPositionAndSize.right - cilentPositionAndSize.left;
    int height = cilentPositionAndSize.bottom - cilentPositionAndSize.top;

    _winInfo.hMainWnd = CreateWindow(_winInfo.mainWndclassName,
                                     _winInfo.mainWndCaption,
                                     WS_OVERLAPPEDWINDOW,
                                     CW_USEDEFAULT,
                                     CW_USEDEFAULT,
                                     width,
                                     height,
                                     0,
                                     0,
                                     _winInfo.hInstance,
                                     0);

    if (!_winInfo.hMainWnd)
    {
        MessageBox(0, L"CreateWindow �Լ� ȣ�� ����.", 0, 0);
        return;
    }

    ShowWindow(_winInfo.hMainWnd, SW_SHOW);
    UpdateWindow(_winInfo.hMainWnd);
}