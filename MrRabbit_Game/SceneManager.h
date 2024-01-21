/// SceneManager.h : ���� �����ϴ� �޴��� �Դϴ�.
///
/// 2023-12-26


#pragma once

#include "ForGraphics.h"
#include "EntityEnum.h"
#include "Entity.h"

#include <list>
#include <memory>

namespace core{ template <typename T>class EntityManager; }

using WeakEntityPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace game
{
class IScene;
class EntityFactory;

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

    void ExportData(data::ForGraphics* info);

    WeakEntityPtr GetEntity(const char* name);

    IScene* GetCurrentScene();

private:
    std::unique_ptr<core::EntityManager<EntityFactory>> _entityManager;
    std::shared_ptr<IScene>        _currenScene{nullptr};
    SceneStatus                    _status{SceneStatus::UNKNOWN};

    // �׷��Ƚ����� ���� ������
    std::unique_ptr<data::ForGraphics> _currentGraphicsInfo;
};

} // namespace game