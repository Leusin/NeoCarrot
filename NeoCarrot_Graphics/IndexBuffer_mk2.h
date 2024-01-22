/// IndexBuffer_mk2.h
/// 인덱스 버퍼없이 버텍스 버퍼만으로 device->Draw 할 수 있는 경우가 있어서 분리하였다.
/// 또한 effec tframeWork 를 사용하지 않는다는 전제하에 업데이트된다.
///
/// 2024-01-22

#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <d3d11.h>
#include <wrl.h>

namespace graphics
{
class D3Devices;

// 본문
class IndexBuffer_mk2: public core::IComponent, virtual core::GetEntity
{
public:
    IndexBuffer_mk2(EntityPtr entityPtr);

public:
    void Awake() override;
    void Update(float dt) override;

public:
    // 0. 어딘가에서 _indices 를 초기화 하는 것이 선행되어야 한다.
    void GetIndices(const std::vector<WORD>& indices);

private:
    // 1. 그 뒤 인덱스 버퍼를 초기화한다.
    void InitilaizeVertexBuffer();

    void UpdateInputAssemBler();

private:
    D3Devices* _d3devices;

    std::vector<WORD> _indices;
    Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer{ nullptr };

public:
    // 아래 변수는 언젠가 사용하겠지?
    std::vector<unsigned int> _indexOffset;
    std::vector<unsigned int> _indexCount;
    unsigned int _totalIndexCount{ 0 };
};

} // namespace graphics