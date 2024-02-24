#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <array>

namespace graphics
{
static const unsigned bufferCount{ 2 };

class DeferredBuffers
{
public:
    DeferredBuffers();
    DeferredBuffers(const DeferredBuffers&);
    ~DeferredBuffers();

    void Initialize(ID3D11Device* device, int width, int height);
    void Finalize();

    void SetRenderTargets(ID3D11DeviceContext* deviceContext);
    void ClearRenderTargets(ID3D11DeviceContext* deviceContext);

    ID3D11ShaderResourceView* GetShaderResourceView(int view);

private:
    std::array<Microsoft::WRL::ComPtr<ID3D11Texture2D>, bufferCount> _rtTextures;
    std::array<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>, bufferCount> _rtViews;
    std::array<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, bufferCount> _srViews;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _dsBuffer{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _dsView{ nullptr };

    D3D11_VIEWPORT _viewPort;
};

} // namespace