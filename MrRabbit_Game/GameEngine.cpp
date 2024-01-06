#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include "GameEngine.h"

#include "GraphicsEngine.h"
#include "WindowInfomation.h"

game::GameEngine::GameEngine(WindowInfomation* wi) :
// �ʿ��� ������� �ʱ�ȭ ���̴�.
_windowInfo(wi),
_managerCreator{std::make_unique<ManagerCreator>()}
{

#ifdef _DEBUG
    std::cout << "GameEngine\n";
#endif // _DEBUG



#pragma region Manager

    _managers.push_back(_managerCreator->CreateManager(ManagerType::Scene));
    _managers.push_back(_managerCreator->CreateManager(ManagerType::Resource));
    _managers.push_back(_managerCreator->CreateManager(ManagerType::Entity));

#pragma endregion Manager
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

    for (auto& e : _managers)
    {
        e->Initialize();
    }
}

void game::GameEngine::Process()
{
    MSG msg = {0};

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else // Windows �޽����� ������ �ִϸ��̼�/���� �۾��� ����
        {
            /// TODO: ������ ��
            // 1. �ð� ó��
            // 2. �Է� ó��
            // 3. ������Ʈ
            // 4. ������
            // 4.1. ����� ������ ���
            // 5. �̺�Ʈ ó��?

            for (auto& e : _managers)
            {
                e->Update();
            }

            _graphicsEngine->Update(float());
            _graphicsEngine->BeginRender();
            _graphicsEngine->Render();
            _graphicsEngine->EndRender();
        }
    }
}

void game::GameEngine::Finalize()
{
    for (auto& e : _managers)
    {
        e->Finalize();
    }
    _graphicsEngine->Finalize();
}

LRESULT game::GameEngine::MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_ACTIVATE: // ���� Ÿ�̸� ���� ���� �� ȣ���� �Լ� ����
            break;

        case WM_SIZE: // â ����� �缳�� �� �� ȣ��
        {
            if (_graphicsEngine.get() == nullptr)
                break;

            _windowInfo->clientWidth  = LOWORD(lParam);
            _windowInfo->clientHeight = HIWORD(lParam);

            int _resizeWidth  = _windowInfo->clientWidth;
            int _resizeHeight = _windowInfo->clientHeight;

            switch (wParam)
            {
                case SIZE_MINIMIZED: // â �ּ�ȭ
                    _graphicsEngine->OnResize(_resizeWidth, _resizeHeight);
                    break;
                case SIZE_MAXIMIZED: // â �ִ�ȭ
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
