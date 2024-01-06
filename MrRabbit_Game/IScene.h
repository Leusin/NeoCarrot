#pragma once

#include <memory>

namespace game
{
class IScene
{
public:
    virtual ~IScene(){};

public:
    virtual void Initialize() abstract;
    virtual void Update() abstract;
    virtual void Finalize() abstract;

public:
    virtual std::shared_ptr<IScene> NextSene() abstract;
};

} // namespace game