#include "GraphicsEngine.h"
#include "D3D11Context.h"
#include "RenderStates.h"
#include "Font.h"
#include "FontType.h"
#include "Camera3D.h"

// Mesh Obj
#include "Grid.h"

#include <cassert>

ge::GraphicsEngine::GraphicsEngine(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight)
	: _d3d11(std::make_unique<D3D11Context>(hinst, hWnd, clientWidth, clientHeight))
	, _renderState(std::make_unique<RenderStates>(_d3d11->Divice()))
	, _font(std::make_unique<Font>(_d3d11->Divice(), _d3d11->DiviceContext(), _renderState->Solid(), _renderState->_normalDSS, FontType::gulima9k))
	, _grid(std::make_unique<Grid>(_d3d11->Divice(), _d3d11->DiviceContext(), _renderState->WireFrame()))
	, _camera(std::make_unique<Camera3D>())
{
    // 카메라 초기화
    _camera->SetPosition(0.0f, 2.0f, -15.0f);
    _camera->LookAt(DirectX::XMFLOAT3(20.f, 20.f, -20.f), DirectX::XMFLOAT3(0.f, 6.f, -6.f),
                    DirectX::XMFLOAT3(0.f, 1.f, 0.f));
}

ge::GraphicsEngine::~GraphicsEngine()
{
}

void ge::GraphicsEngine::Initialize()
{

}

void ge::GraphicsEngine::Update(float deltaTime)
{
    _camera->UpdateViewMatrix();
}

void ge::GraphicsEngine::BeginRender()
{
	_d3d11->BeginRender();
}

void ge::GraphicsEngine::Render()
{
	_font->DrawTest();
	_grid->Render();
}

void ge::GraphicsEngine::EndRender()
{
	_d3d11->EndRender();
}

void ge::GraphicsEngine::Finalize()
{
}

void ge::GraphicsEngine::OnResize(int clientWidth, int clientHeight)
{
	_d3d11->OnResize(clientWidth, clientHeight);

	// 화면비
    float aspectRatio = static_cast<float>(clientWidth) / clientHeight;
	
	// 업데이트
    _camera->SetLens(0.25f, aspectRatio, 1.0f, 1000.0f);
}
