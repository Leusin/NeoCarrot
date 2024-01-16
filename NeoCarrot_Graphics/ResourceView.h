/// 2024-01-15

#pragma once

#include <d3d11.h>
#include <wrl.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


namespace graphics
{

struct ResourceView
{
    ResourceView()
    {
#ifdef _DEBUG
        std::cout << "\t\tResourceView Constructed\n";
#endif // _DEBUG
    }

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
