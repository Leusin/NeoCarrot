/// Object.h : Entity(Game Obejct)�� �����ϴ� Ŭ����
///
/// 2024-01-06

#pragma once

#include "IManager.h"

namespace game
{

class EntityManager : public IManager
{
public:
    EntityManager();
    ~EntityManager();

    void Initialize() override;
    void Update() override;
    void Finalize() override;
};

}