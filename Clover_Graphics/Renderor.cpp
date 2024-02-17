#include "Renderor.h"

namespace graphics
{

D3D11Renderor::D3D11Renderor(HINSTANCE& hinst, HWND hWnd, int clientWidth, int clientHeight)
    : _d3d11{ std::make_unique<D3D11Context>(hinst, hWnd, clientWidth, clientHeight) }
    , _camera{ std::make_unique<Camera>() }
    , _light{ std::make_unique<Light>() }
    , _model{ std::make_unique<Model>() }
    //, _colorShader{ std::make_unique<ColorShader>() }
    , _textureShader{ std::make_unique<TextureShader>() }
    , _lightShader{ std::make_unique<LightShader>() }
{
    _camera->SetPosition(0.f, 0.f, -5.f);
}

D3D11Renderor::D3D11Renderor(const D3D11Renderor&)
{
}

D3D11Renderor::~D3D11Renderor()
{
}

void D3D11Renderor::Initialize()
{
    //_colorShader->Initialize(_d3d11->GetDevice());
    _textureShader->Initialize(_d3d11->GetDevice());
    _lightShader->Initialize(_d3d11->GetDevice());

    _model->Initialize(_d3d11->GetDevice(),
        _d3d11->GetDeviceContext(),
        L"../Resource/Texture/WoodCrate01.dds");

    _light->SetDiffuseColor(1.f, 0.f, 1.f, 1.f);
    _light->SetDirection(0.f, 0.f, 1.f);
}

void D3D11Renderor::Update(float deltaTime)
{
    Render();
}

void D3D11Renderor::Finalize()
{
    _d3d11->Finalize();
}

void D3D11Renderor::OnResize(int clientWidth, int clientHeight)
{
    _d3d11->OnResize(clientWidth, clientHeight);
}

void D3D11Renderor::Render()
{
    // 버퍼 지우기
    // const float Carrot[4] = {0.999f, 0.444f, 0.f, 1.0f};
    const float Dark[4] = { 0.128f, 0.121f, 0.121f, 1.0f };
    _d3d11->BeginRender(Dark);

    // 카메라 위치에 따른 뷰 행렬 생성
    _camera->Render();

    // 카메라와 d3d 객체에서 월드, 뷰, 투영 행렬을 가져옴
    DirectX::XMMATRIX world = _d3d11->GetWorldMatrix();
    DirectX::XMMATRIX view  = _camera->GetViewMatrix();
    DirectX::XMMATRIX proj  = _d3d11->GetProjectMatrix();

    // 회전 ***
    static float rotation = 0.f;
    if (rotation > 360.f) rotation -= 360.f;
    rotation += (float)DirectX::XM_PI * 0.0001f;
    world = DirectX::XMMatrixRotationY(rotation);

    // 모델의 버텍스 버퍼와 인덱스 버퍼를 파이프라인에 세팅
    _model->Render(_d3d11->GetDeviceContext());

    // 셰이더를 통한 모델 렌더링
    // _colorShader->Render(_d3d11->GetDeviceContext(), 3, world, view, proj);
    //_textureShader->Render(_d3d11->GetDeviceContext(), 3, world, view, proj, _model->GetTexture());
    _lightShader->Render(_d3d11->GetDeviceContext(),
        3,
        world,
        view,
        proj,
        _model->GetTexture(),
        _light->GetDirection(),
        _light->GetDiffuseColor());

    // 버퍼의 내용을 화면에 출력
    _d3d11->EndRender();
}

} // namespace graphics