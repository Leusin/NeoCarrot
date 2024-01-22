/// IndexBuffer_mk2.h
/// �ε��� ���۾��� ���ؽ� ���۸����� device->Draw �� �� �ִ� ��찡 �־ �и��Ͽ���.
/// ���� effec tframeWork �� ������� �ʴ´ٴ� �����Ͽ� ������Ʈ�ȴ�.
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

// ����
class IndexBuffer_mk2: public core::IComponent, virtual core::GetEntity
{
public:
    IndexBuffer_mk2(EntityPtr entityPtr);

public:
    void Awake() override;
    void Update(float dt) override;

public:
    // 0. ��򰡿��� _indices �� �ʱ�ȭ �ϴ� ���� ����Ǿ�� �Ѵ�.
    void GetIndices(const std::vector<WORD>& indices);

private:
    // 1. �� �� �ε��� ���۸� �ʱ�ȭ�Ѵ�.
    void InitilaizeVertexBuffer();

    void UpdateInputAssemBler();

private:
    D3Devices* _d3devices;

    std::vector<WORD> _indices;
    Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer{ nullptr };

public:
    // �Ʒ� ������ ������ ����ϰ���?
    std::vector<unsigned int> _indexOffset;
    std::vector<unsigned int> _indexCount;
    unsigned int _totalIndexCount{ 0 };
};

} // namespace graphics