/// 2024-01-15

#pragma once

#include <wrl.h>
#include <d3d11.h>

namespace graphics
{

struct ResourceView
{
    ResourceView();

    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
};

} // namespace graphics

//
// ���ҽ� ���� ����.
// 
// - ID3D11DepthStencilView : ���� ���ٽ� �׽��� �� �� �ؽ�ó ���ҽ� ����
// - ID3D11RenderTargetView : ���� Ÿ���� �ؽ�ó �� ����
// - ID3D11ShaderResourceView : ��� ����, �ؽ�ó ����, �ؽ�ó�� ���÷� ���� �����Ϳ� ����
// - ID3D11UnorderedAccessView : �ȼ� ���̴��� ��ǻƮ ���̴��� ����Ͽ� ���ĵ��� ���� ���ҽ��� ����
// 
// 2024-01-15
