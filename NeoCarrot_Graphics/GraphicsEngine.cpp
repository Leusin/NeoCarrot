#include "GraphicsEngine.h"

#include "D3D11Context_mk2.h"
#include "DXTKFont.h"
#include "FontType.h"
#include "Camera3D.h"
#include "ModelManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


namespace graphics
{

graphics::GraphicsEngine::GraphicsEngine(HINSTANCE& hinst, HWND hWnd, int clientWidth, int clientHeight) 
    : _d3d11context(std::make_unique<D3D11Context_mk2>(hinst, hWnd, clientWidth, clientHeight))
    , _font(std::make_unique<DXTKFont>(_d3d11context->GetDevices(), _d3d11context->GetRenderStates(), FontType::gulima9k))
    , _camera(std::make_unique<Camera3D>(clientWidth, clientHeight))
{
    _modelManager = std::make_unique<ModelManager>(_d3d11context.get(), _camera.get());

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
    auto view = _camera->View();
    auto proj = _camera->Proj();
    auto eye = _camera->GetPosition();

}

void graphics::GraphicsEngine::BeginRender()
{
    const float Carrot[4] = {0.999f, 0.444f, 0.f, 1.0f};
    _d3d11context->BeginRender(Carrot);
}

void graphics::GraphicsEngine::Render()
{
	_font->DrawTest();
    _modelManager->Update(0);

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

}