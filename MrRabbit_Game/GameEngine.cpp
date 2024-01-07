#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "WindowInfomation.h"

game::GameEngine::GameEngine(WindowInfomation* wi) :
// 필요한 순서대로 초기화 중이다.
_windowInfo(wi),
_sceneManager{std::make_unique<SceneManager>()},
_timeManager{std::make_unique<TimeManager>()}
{

#ifdef _DEBUG
    std::cout << "GameEngine Constructed\n";
#endif // _DEBUG
}

game::GameEngine::~GameEngine()
{
}

void game::GameEngine::Initialize()
{
    _graphicsEngine = std::make_unique<grahics::GraphicsEngine>(_windowInfo->hInstance,
                                                                _windowInfo->hMainWnd,
                                                                _windowInfo->clientWidth,
                                                                _windowInfo->clientHeight);

    _sceneManager->Initialize();
}

void game::GameEngine::Process()
{
    MSG msg = {0};

    _timeManager->Reset();

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else // Windows 메시지가 없으면 애니메이션/게임 작업을 수행
        {
            /// TODO: 구현할 것
            // 1. 시간 처리
            _timeManager->Tick();
            // 2. 입력 처리
            // 3. 업데이트
            _sceneManager->Update();
            // 4. 랜더링
            // 4.1. 디버그 데이터 출력
            // 5. 이벤트 처리?

            /// TODO:
            /// gameEngine 은 Component로서 동작하도록 바꿀 것...
            /// 아니면 렌더러가 객체가 따로 이곳에서 랜더링 할 것인가..?
            _graphicsEngine->Update(float());
            _graphicsEngine->BeginRender();
            _graphicsEngine->Render();
            _graphicsEngine->EndRender();
        }
    }
}

void game::GameEngine::Finalize()
{
    _sceneManager->Finalize();
    _graphicsEngine->Finalize();
}

LRESULT game::GameEngine::MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_ACTIVATE: // 게임 타이머 정지 여부 및 호출할 함수 설정
            break;

        case WM_SIZE: // 창 사이즈가 재설정 될 때 호출
        {
            if (_graphicsEngine.get() == nullptr)
                break;

            _windowInfo->clientWidth  = LOWORD(lParam);
            _windowInfo->clientHeight = HIWORD(lParam);

            int _resizeWidth  = _windowInfo->clientWidth;
            int _resizeHeight = _windowInfo->clientHeight;

            switch (wParam)
            {
                case SIZE_MINIMIZED: // 창 최소화
                    _graphicsEngine->OnResize(_resizeWidth, _resizeHeight);
                    break;
                case SIZE_MAXIMIZED: // 창 최대화
                    _graphicsEngine->OnResize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
                    break;
                case SIZE_RESTORED:
                    _graphicsEngine->OnResize(_resizeWidth, _resizeHeight);
                    break;
                default:
                    _graphicsEngine->OnResize(_resizeWidth, _resizeHeight);
                    break;
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
            // 창이 너무 작아지지 않도록
            ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
            ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
            break;

        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
            break;
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
            break;
        case WM_MOUSEMOVE:
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
