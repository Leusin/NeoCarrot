/// ResourceManager.h : ���ӿ������� �ʿ��� ���ҽ��� �����ϴ� Ŭ�����Դϴ�.
/// 
/// ������ � ���ҽ��� �����ؾ��� �� �� ��?����
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