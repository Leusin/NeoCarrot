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

namespace graphics
{

graphics::GraphicsEngine::GraphicsEngine(HINSTANCE& hinst, HWND hWnd, int clientWidth, int clientHeight) 
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

graphics::GraphicsEngine::~GraphicsEngine()
{
}

void graphics::GraphicsEngine::Initialize()
{
    _camera->Initialize();
}

void graphics::GraphicsEngine::Update(float deltaTime)
{
    _grid->_transpose.SetTM(DirectX::XMMatrixIdentity(), _camera->View(), _camera->Proj());
    
    _grid->SetEyePosW(_camera->GetPosition());

    BeginRender();
    Render();
    EndRender();
}

void graphics::GraphicsEngine::BeginRender()
{
	_d3d11->BeginRender();
}

void graphics::GraphicsEngine::Render()
{
	_font->DrawTest();
	_grid->Render();
    DrawStatus();
}

void graphics::GraphicsEngine::EndRender()
{
	_d3d11->EndRender();
}

void graphics::GraphicsEngine::Finalize()
{
}

void graphics::GraphicsEngine::OnResize(int clientWidth, int clientHeight)
{
	_d3d11->OnResize(clientWidth, clientHeight);

	// ȭ���
    float aspectRatio = static_cast<float>(clientWidth) / clientHeight;
	
	// ������Ʈ
    _camera->SetLens(aspectRatio);
}

void GraphicsEngine::DrawStatus()
{
    // ��ó ����
    int xPad   = 44;
    int yPad   = 44;
    int lSpace = 18;

    // ī�޶� ����
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