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
// 리소스 뷰의 종류.
// 
// - ID3D11DepthStencilView : 뎁스 스텐실 테스팅 할 때 텍스처 리소스 접근
// - ID3D11RenderTargetView : 랜더 타깃의 텍스처 에 접근
// - ID3D11ShaderResourceView : 상수 버퍼, 텍스처 버퍼, 텍스처나 샘플러 같은 셰이터에 접근
// - ID3D11UnorderedAccessView : 픽셀 셰이더나 컴퓨트 셰이더를 사용하여 정렬되지 않은 리소스에 접근
// 
// 2024-01-15
