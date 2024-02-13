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
        else // Windows �޽����� ������ �ִϸ��̼�/���� �۾��� ����
        {
            // 1. �ð� ó��
            // 2. �Է� ó��(����)
            // 3. Scene ������Ʈ
            // 4. ������ ������Ʈ
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
        case WM_ACTIVATE: // ���� Ÿ�̸� ���� ���� �� ȣ���� �Լ� ����
            break;

        case WM_SIZE: // â ����� �缳�� �� �� ȣ��
        {
            if (this == nullptr || _renderer.get() == nullptr) break;

            _windowInfo->clientWidth  = LOWORD(lParam);
            _windowInfo->clientHeight = HIWORD(lParam);

            int _resizeWidth  = _windowInfo->clientWidth;
            int _resizeHeight = _windowInfo->clientHeight;

            switch (wParam)
            {
                case SIZE_MINIMIZED: // â �ּ�ȭ
                {
                    _renderer->OnResize(_resizeWidth, _resizeHeight);
                    break;
                }
                case SIZE_MAXIMIZED: // â �ִ�ȭ
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

        case WM_ENTERSIZEMOVE: // â �׵θ��� ����� ��
            break;

        case WM_EXITSIZEMOVE: // â �׵θ��� ������ ��
            break;

        case WM_DESTROY: // â�� �Ҹ�Ǿ��� ��
            PostQuitMessage(0);
            break;

        case WM_MENUCHAR:
            // alt-enter �� ������ �Ҹ��� �ȳ�����
            return MAKELRESULT(0, MNC_CLOSE);

        case WM_GETMINMAXINFO:
        {
            // â�� �ʹ� �۾����� �ʵ���
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

        // Ű���尡 ������ �� ó��
        case WM_KEYDOWN:
        {
            _input->KeyDown((unsigned int)wParam);
            break;
        }

        // Ű���尡 �������� �� ó��
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
/*
game::GameEngine::GameEngine(data::WindowInfo* wi)
// �ʿ��� ������� �ʱ�ȭ ���̴�.
    : _windowInfo(wi)
    , _graphicsInfo{std::make_unique<data::ForGraphics>()}
    , _sceneManager{std::make_unique<SceneManager>()}
    , _timeManager{std::make_unique<TimeManager>()}
    , _inputManager{std::make_unique<InputManager>(&wi->hMainWnd)}
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
    _renderer =
std::make_unique<graphics::GraphicsEngine>(_windowInfo->hInstance,
                                                            _windowInfo->hMainWnd,
                                                          _windowInfo->clientWidth,
                                                          _windowInfo->clientHeight);

    _sceneManager->Initialize();
    _sceneManager->ExportData(_graphicsInfo.get());
    _renderer->ImportData(_graphicsInfo.get());

    _renderer->Initialize();

    auto* currScene = _sceneManager->GetCurrentScene();
    _inputManager->_currentscene = currScene;

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
        else // Windows �޽����� ������ �ִϸ��̼�/���� �۾��� ����
        {
            // 1. �ð� ó��
            // 2. �Է� ó��(����)
            // 3. Scene ������Ʈ
            // 4. ������ ������Ʈ

            _timeManager->Tick();
            float dt = _timeManager->DeltaTime();

            _sceneManager->Update(dt);
            _sceneManager->ExportData(_graphicsInfo.get());

            _renderer->ImportData(_graphicsInfo.get());
            _renderer->Update(dt);

            _renderer->BeginRender();
            _renderer->Render();
            _renderer->EndRender();

        }
    }
}

void game::GameEngine::Finalize()
{
    _sceneManager->Finalize();
    _renderer->Finalize();
}

LRESULT game::GameEngine::MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM
lParam)
{
    switch (msg)
    {
        case WM_ACTIVATE: // ���� Ÿ�̸� ���� ���� �� ȣ���� �Լ� ����
            break;

        case WM_SIZE: // â ����� �缳�� �� �� ȣ��
        {
            if (_renderer.get() == nullptr)
                break;

            _windowInfo->clientWidth  = LOWORD(lParam);
            _windowInfo->clientHeight = HIWORD(lParam);

            int _resizeWidth  = _windowInfo->clientWidth;
            int _resizeHeight = _windowInfo->clientHeight;

            switch (wParam)
            {
                case SIZE_MINIMIZED: // â �ּ�ȭ
                    _renderer->OnResize(_resizeWidth, _resizeHeight);
                    break;
                case SIZE_MAXIMIZED: // â �ִ�ȭ
                    _renderer->OnResize(GetSystemMetrics(SM_CXSCREEN),
GetSystemMetrics(SM_CYSCREEN)); break; case SIZE_RESTORED:
_renderer->OnResize(_resizeWidth, _resizeHeight); break; default:
_renderer->OnResize(_resizeWidth, _resizeHeight); break;
            }
        }
        break;

        case WM_ENTERSIZEMOVE: // â �׵θ��� ����� ��
            break;

        case WM_EXITSIZEMOVE: // â �׵θ��� ������ ��
            break;

        case WM_DESTROY: // â�� �Ҹ�Ǿ��� ��
            PostQuitMessage(0);
            break;

        case WM_MENUCHAR:
            // alt-enter �� ������ �Ҹ��� �ȳ�����
            return MAKELRESULT(0, MNC_CLOSE);

        case WM_GETMINMAXINFO:
            // â�� �ʹ� �۾����� �ʵ���
            ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
            ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
            break;

        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
            _inputManager->OnMouseDown(wParam, GET_X_LPARAM(lParam),
GET_Y_LPARAM(lParam)); break; case WM_LBUTTONUP: case WM_MBUTTONUP: case
WM_RBUTTONUP: _inputManager->OnMouseUp(wParam, GET_X_LPARAM(lParam),
GET_Y_LPARAM(lParam)); break; case WM_MOUSEMOVE:
_inputManager->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
break; default: return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
*/
