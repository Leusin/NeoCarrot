/// GameProcess.cpp : 게임의 흐름을 제어 및 관리합니다.
/// 대부분 매니저 클래스들을 여기에 있습니다.
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
    // 윈도우 정보.
    // 초기화 및  MassageProc에서 사용한다.
    data::WindowInfo* _windowInfo;

    std::unique_ptr<data::ForGraphics>  _graphicsInfo;

    std::unique_ptr<SceneManager> _sceneManager;
    std::unique_ptr<TimeManager>  _timeManager;

    // 그래픽 엔진
    std::unique_ptr<graphics::GraphicsEngine> _renderer{nullptr};
};

} // namespace game