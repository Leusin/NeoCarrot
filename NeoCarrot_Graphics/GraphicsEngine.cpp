#include "GraphicsEngine.h"

#include "D3D11Context.h"
#include "D3D11RenderStates.h"
#include "DXTKFont.h"
#include "FontType.h"
#include "Camera3D.h"

// Mesh Obj
#include "Grid.h"
#include "ForGraphics.h"
#include "ResourceManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <cassert>

namespace grahics
{

grahics::GraphicsEngine::GraphicsEngine(HINSTANCE& hinst, HWND hWnd, int clientWidth, int clientHeight) 
    :_d3d11(std::make_unique<D3D11Context>(hinst, hWnd, clientWidth, clientHeight))
	, _renderState(std::make_unique<RenderStates>(_d3d11->Divice()))
	, _font(std::make_unique<Font>(_d3d11->Divice(), _d3d11->DiviceContext(), _renderState->Solid(), _renderState->_normalDSS, FontType::gulima9k))
	, _grid(std::make_unique<Grid>(_d3d11->Divice(), _d3d11->DiviceContext(), _renderState->WireFrame()))
    , _camera(std::make_unique<Camera3D>(clientWidth, clientHeight))
    , _resourceManager(std::make_unique<ResourceManager>())
{
#ifdef _DEBUG
    std::cout << "GraphicsEngine Constructed\n";
#endif // _DEBUG
}

grahics::GraphicsEngine::~GraphicsEngine()
{
}

void grahics::GraphicsEngine::Initialize()
{
    _camera->Initialize();
}

void grahics::GraphicsEngine::Update(float deltaTime)
{
    _grid->_transpose.SetTM(DirectX::XMMatrixIdentity(), _camera->View(), _camera->Proj());
    
    _grid->SetEyePosW(_camera->GetPosition());

    BeginRender();
    Render();
    EndRender();
}

void grahics::GraphicsEngine::BeginRender()
{
	_d3d11->BeginRender();
}

void grahics::GraphicsEngine::Render()
{
	_font->DrawTest();
	_grid->Render();
    DrawStatus();
}

void grahics::GraphicsEngine::EndRender()
{
	_d3d11->EndRender();
}

void grahics::GraphicsEngine::Finalize()
{
}

void grahics::GraphicsEngine::OnResize(int clientWidth, int clientHeight)
{
	_d3d11->OnResize(clientWidth, clientHeight);

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