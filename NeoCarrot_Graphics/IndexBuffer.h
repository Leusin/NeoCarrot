#pragma once

#include "IComponent.h"
#include "GetEntity.h"
#include "Mesh.h"

#include <d3d11.h>
#include <vector>
#include <wrl.h>

namespace graphics
{
class D3Devices;

class IndexBuffer : public core::IComponent, virtual core::GetEntity
{
public:
    IndexBuffer(EntityPtr entityPtr);

    void Awake() override;

    void SetFromMesh(const model::Mesh& data);

    // �ε�������
    Microsoft::WRL::ComPtr<ID3D11Buffer> _ib{nullptr};
    std::vector<UINT> _indices;

    std::vector<UINT> _indexOffset;
    std::vector<UINT> _indexCount;

    UINT _totalIndexCount;

private:
    D3Devices* _d3device{ nullptr };
};
} // namespace graphics