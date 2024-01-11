/// GameProcess.cpp : ������ �帧�� ���� �� �����մϴ�.
/// ��κ� �Ŵ��� Ŭ�������� ���⿡ �ֽ��ϴ�.
///
/// 2023-12-22


#pragma once

#include <memory>
#include <vector>
#include <windows.h>

namespace graphics{ class GraphicsEngine; }
namespace data{ struct WindowInfo; }
namespace data{ struct ForGraphics; }

namespace game
{
class IManger;
class ManagerCreator;
class SceneManager;
class TimeManager;

class GameEngine
{
public:
    GameEngine(data::WindowInfo* winInfo);
    ~GameEngine();

    void Initialize();
    void Process();
    void Finalize();

    LRESULT MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    // ������ ����.
    // �ʱ�ȭ ��  MassageProc���� ����Ѵ�.
    data::WindowInfo* _windowInfo;

    std::unique_ptr<data::ForGraphics>  _graphicsInfo;

    std::unique_ptr<SceneManager> _sceneManager;
    std::unique_ptr<TimeManager>  _timeManager;

    // �׷��� ����
    std::unique_ptr<graphics::GraphicsEngine> _renderer{nullptr};
};

} // namespace game