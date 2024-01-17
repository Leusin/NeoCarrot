#include <d3d11.h>
#include <directxmath.h>

class ColorShader
{
private:
    struct MatrixBufferType
    {
        DirectX::XMMATRIX world;
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX projection;
    };

public:
    ColorShader();
    ~ColorShader();

    bool Initialize(ID3D11Device* device, HWND hwnd);
    void Shutdown();
    bool Render(ID3D11DeviceContext* deviceContext,
                int                  indexCount,
                DirectX::XMMATRIX    worldMatrix,
                DirectX ::XMMATRIX   viewMatrix,
                DirectX ::XMMATRIX   projectionMatrix);

private:
    ID3D11VertexShader* m_vertexShader{nullptr};
    ID3D11PixelShader*  m_pixelShader{nullptr};
    ID3D11InputLayout*  m_layout{nullptr};
    ID3D11Buffer*       m_matrixBuffer{nullptr};
};

ColorShader::ColorShader()
{
}

ColorShader::~ColorShader()
{
}
