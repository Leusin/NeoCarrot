#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace graphics
{

struct RenderStates
{
    RenderStates(ID3D11Device* _d3dDevice);
    ~RenderStates();


    Microsoft::WRL::ComPtr<ID3D11RasterizerState> wireframeRS{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> solidRS{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> normalDSS{ nullptr }; //ÆùÆ®¿ë. 

private:
    void CreateWireFrameRanderState(ID3D11Device* _d3dDevice);
    void CreateSolidRenderState(ID3D11Device* _d3dDevice);

    void CreateNormalDepthStencilState(ID3D11Device* _d3dDevice);
};

}