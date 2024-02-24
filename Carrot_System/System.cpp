#include "System.h"

#include <windowsx.h>

namespace game
{
System::System(data::WindowInfo* winInfo)
    : _windowInfo(winInfo)
    , _input{ std::make_unique<Input>(&winInfo->hMainWnd) }
{
}

System::~System()
{
}

void System::Initialize()
{
    _renderer = std::make_unique<graphics::D3D11Renderor>(_windowInfo->hInstance,
                                                          _windowInfo->hMainWnd,
                                                          _windowInfo->clientWidth,
                                                          _windowInfo->clientHeight);

    _input->Initialize();
    _renderer->Initialize();
}

void System::Process()
{
    MSG msg = { 0 };

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else // Windows 메시지가 없으면 애니메이션/게임 작업을 수행
        {
            // 1. 시간 처리
            // 2. 입력 처리(생략)
            // 3. Scene 업데이트
            // 4. 랜더러 업데이트
            //_input->Frame();
            _renderer->Update(0.f);
        }
    }
}

void System::Finalize()
{
    _renderer->Finalize();
    //UnregisterClass();
}

LRESULT System::MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_ACTIVATE: // 게임 타이머 정지 여부 및 호출할 함수 설정
            break;

        case WM_SIZE: // 창 사이즈가 재설정 될 때 호출
        {
            if (this == nullptr || _renderer.get() == nullptr) break;

            _windowInfo->clientWidth  = LOWORD(lParam);
            _windowInfo->clientHeight = HIWORD(lParam);

            int _resizeWidth  = _windowInfo->clientWidth;
            int _resizeHeight = _windowInfo->clientHeight;

            switch (wParam)
            {
                case SIZE_MINIMIZED: // 창 최소화
                {
                    _renderer->OnResize(_resizeWidth, _resizeHeight);
                    break;
                }
                case SIZE_MAXIMIZED: // 창 최대화
                {
                    _renderer->OnResize(GetSystemMetrics(SM_CXSCREEN),
                                        GetSystemMetrics(SM_CYSCREEN));
                    break;
                }
                case SIZE_RESTORED:
                {
                    _renderer->OnResize(_resizeWidth, _resizeHeight);
                    break;
                }
                default:
                {
                    _renderer->OnResize(_resizeWidth, _resizeHeight);
                    break;
                }
            }
        }
        break;

        case WM_ENTERSIZEMOVE: // 창 테두리를 잡았을 때
            break;

        case WM_EXITSIZEMOVE: // 창 테두리를 놓았을 때
            break;

        case WM_DESTROY: // 창이 소멸되었을 때
            PostQuitMessage(0);
            break;

        case WM_MENUCHAR:
            // alt-enter 를 누르면 소리가 안나도록
            return MAKELRESULT(0, MNC_CLOSE);

        case WM_GETMINMAXINFO:
        {
            // 창이 너무 작아지지 않도록
            ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
            ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
            break;
        }

        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        {
            _input->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        }
        
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        {
            _input->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        }
        
        case WM_MOUSEMOVE:
        {
            _input->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        }

        // 키보드가 눌렸을 때 처리
        case WM_KEYDOWN:
        {
            _input->KeyDown((unsigned int)wParam);
            break;
        }

        // 키보드가 떨어졌을 때 처리
        case WM_KEYUP:
        {
            _input->KeyUp((unsigned int)wParam);
            break;
        }

        default:
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
            break;
        }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

} // namespace game
