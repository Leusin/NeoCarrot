#pragma once

#include "Entity.h"
#include "EntityEnum.h"
#include "IComponent.h"

#include <d3d11.h>
#include <vector>
#include <wrl.h>

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{
class D3Device;

class IndexBuffer : public core::IComponent
{
public:
    IndexBuffer(EntityPtr entityPtr);

    void Awake() override;

private:
    EntityWeakPtr _entity;
    D3Device*     _d3device;

    // ÀÎµ¦½º¹öÆÛ
    Microsoft::WRL::ComPtr<ID3D11Buffer> _ib{nullptr};

    std::vector<UINT> _indices;
    std::vector<UINT> _indexOffset;
    std::vector<UINT> _indexCount;

    UINT _totalIndexCount;
};
} // namespace graphics