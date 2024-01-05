/// ResourceManager.h : 게임엔진에서 필요한 리소스를 관리하는 클레스입니다.
/// 
/// 하지만 어떤 리소스를 관리해야할 지 잘 몰?루유
/// 
/// 2024-01-04 

#pragma once

#include "IManager.h"

namespace ge
{

class ResourceManager : public IManager
{
public:
    ResourceManager();
    ~ResourceManager();

    void Initialize() override;
    void Update() override;
    void Finalize() override;
};

} // namespace ge