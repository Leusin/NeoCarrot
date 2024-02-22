#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <array>

static const unsigned bufferCount{ 2 };

namespace
{

class DeferredBuffers
{
public:
    DeferredBuffers();
    DeferredBuffers(const DeferredBuffers&) = default;
    ~DeferredBuffers()                      = default;

    void Initialize(ID3D11Device* device, int width, int height);
    void Finalize();
    
    void SetRenderTargets(ID3D11DeviceContext* deviceContext);
    void ClearRenderTargets(ID3D11DeviceContext* deviceContext);

private:
    std::array<Microsoft::WRL::ComPtr<ID3D11Texture2D>, bufferCount> _rtTexture;
    std::array<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>, bufferCount> _rtViews;
    std::array<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, bufferCount> _srViews;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _dsBuffer{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _dsView{ nullptr };

    D3D11_VIEWPORT _viewPort;
};

} // namespace