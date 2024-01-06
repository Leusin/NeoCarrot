/// SceneManager.h : ���� �����ϴ� �޴��� �Դϴ�.
///
/// 2023-12-26
///


#pragma once
#include "IManager.h"

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

class SceneManager : public IManager
{
public:
    SceneManager();
    ~SceneManager();

    void Initialize() override;
    void Update() override;
    void Finalize() override;

private:
    std::shared_ptr<IScene> _currenScene{nullptr};
    SceneStatus             _status;
};

} // namespace game