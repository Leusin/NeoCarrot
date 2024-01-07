/// SceneManager.h : 씬을 관리하는 메니저 입니다.
///
/// 2023-12-26
///


#pragma once
#include <list>
#include <memory>

namespace game
{
class IScene;

enum class SceneStatus
{
    UNKNOWN = -1,
    LOAD    = 0,
    START,
    RUN,
    FINAL,
    QUIT,
};

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void Initialize();
    void Update(float deltaTime);
    void Finalize();

private:
    std::shared_ptr<IScene> _currenScene{nullptr};
    SceneStatus             _status{SceneStatus::UNKNOWN};
};

} // namespace game