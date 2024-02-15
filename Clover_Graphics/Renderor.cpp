#include "Renderor.h"

namespace graphics
{

D3D11Renderor::D3D11Renderor(HINSTANCE& hinst, HWND hWnd, int clientWidth, int clientHeight)
    : _d3d11{ std::make_unique<D3D11Context>(hinst, hWnd, clientWidth, clientHeight) }
    , _camera{ std::make_unique<Camera>() }
    , _model{ std::make_unique<Model>() }
    //, _colorShader{ std::make_unique<ColorShader>() }
    , _textureShader{ std::make_unique<TextureShader>() }
{
    _camera->SetPosition(0.f, 0.f, -0.5f);
}

D3D11Renderor::D3D11Renderor(const D3D11Renderor&)
{
}

D3D11Renderor::~D3D11Renderor()
{
}

void D3D11Renderor::Initialize()
{
    _model->Initialize(_d3d11->GetDevice(), _d3d11->GetDeviceContext(), L"../Resource/Texture/WoodCrate01.dds");
    //_colorShader->Initialize(_d3d11->GetDevice());
    _textureShader->Initialize(_d3d11->GetDevice());
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
    // const float Carrot[4] = {0.999f, 0.444f, 0.f, 1.0f};
    const float Dark[4] = { 0.128f, 0.121f, 0.121f, 1.0f };
    _d3d11->BeginRender(Dark);

    _camera->Render();

    DirectX::XMMATRIX world = _d3d11->GetWorldMatrix();
    DirectX::XMMATRIX view = _camera->GetViewMatrix();
    DirectX::XMMATRIX proj = _d3d11->GetProjectMatrix();

    //_colorShader->Render(_d3d11->GetDeviceContext(), 3, world, view, proj);
    _textureShader->Render(_d3d11->GetDeviceContext(), 3, world, view, proj, _model->GetTexture());
    
    _model->Render(_d3d11->GetDeviceContext());

    _d3d11->EndRender();
}


/*
graphics::GraphicsEngine::GraphicsEngine(HINSTANCE& hinst, HWND hWnd, int
clientWidth, int clientHeight) :
_d3d11context(std::make_unique<D3D11Context_mk2>(hinst, hWnd, clientWidth,
clientHeight)) , _font(std::make_unique<DXTKFont>(_d3d11context->GetDevices(),
_d3d11context->GetRenderStates(), FontType::gulima9k)) ,
_camera(std::make_unique<Camera3D>(clientWidth, clientHeight))
{
    _modelManager = std::make_unique<ModelManager>(_d3d11context.get(),
_camera.get());

#ifdef _DEBUG
    std::cout << "GraphicsEngine Constructed\n";
#endif // _DEBUG
}

graphics::GraphicsEngine::~GraphicsEngine()
{
}

void graphics::GraphicsEngine::Initialize()
{
    _camera->Initialize();
    _modelManager->Initialize();
}

void graphics::GraphicsEngine::Update(float deltaTime)
{
    _dt       = deltaTime;

    auto view = _camera->View();
    auto proj = _camera->Proj();
    auto eye = _camera->GetPosition();

}

void graphics::GraphicsEngine::BeginRender()
{
    //const float Carrot[4] = {0.999f, 0.444f, 0.f, 1.0f};
    const float Dark[4] = {0.128f, 0.121f, 0.121f, 1.0f};
    _d3d11context->BeginRender(Dark);
}

void graphics::GraphicsEngine::Render()
{
    _modelManager->Update(_dt);
    DrawStatus();
}

void graphics::GraphicsEngine::EndRender()
{
    _d3d11context->EndRender();
}

void graphics::GraphicsEngine::Finalize()
{
    _modelManager->Finalize();
}

void graphics::GraphicsEngine::OnResize(int clientWidth, int clientHeight)
{
    _d3d11context->OnResize(clientWidth, clientHeight);

    // 화면비
    float aspectRatio = static_cast<float>(clientWidth) / clientHeight;

    // 업데이트
    _camera->SetLens(aspectRatio);
}

void GraphicsEngine::DrawStatus()
{
    _font->DrawTest();

    // 피처 레벨
    int xPad   = 44;
    int yPad   = 44;
    int lSpace = 18;

    // 카메라 정보
    _font->DrawTextColor(xPad,
                         yPad + 4 * lSpace,
                         DirectX::Colors::MediumSpringGreen,
                         (TCHAR*)L"Camera Pos: %.2f / %.2f / %.2f",
                         _camera->GetPosition().x,
                         _camera->GetPosition().y,
                         _camera->GetPosition().z);
    _font->DrawTextColor(xPad,
                         yPad + 5 * lSpace,
                         DirectX::Colors::MediumSpringGreen,
                         (TCHAR*)L"Camera look: %.2f / %.2f / %.2f",
                         _camera->GetLook().x,
                         _camera->GetLook().y,
                         _camera->GetLook().z);
}

void GraphicsEngine::ImportData(const data::ForGraphics* info)
{
    _camera->GetCameraInfo(info->_camera);
}
*/
} // namespace graphics