/// Object.h : Entity(Game Obejct)를 관리하는 클래스
///
/// 2024-01-06

#pragma once

#include "IManager.h"

#include <vector>
#include <memory>

namespace core
{
template <typename T, typename U>
class Entity;
}

namespace game
{
enum class Tag
{
};
enum class Layer
{
};

class EntityManager : public IManager
{
public:
    EntityManager();
    ~EntityManager();

    void Initialize() override;
    void Update() override;
    void Finalize() override;

private:
   
    std::vector<std::shared_ptr<core::Entity<Tag, Layer>>> _entities;
};

} // namespace game