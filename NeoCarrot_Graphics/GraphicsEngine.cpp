#include "GraphicsEngine.h"
#include "D3D11Context.h"
#include "RenderStates.h"
#include "Font.h"
#include "FontType.h"

// Mesh Obj
#include "Grid.h"

#include <cassert>

ge::GraphicsEngine::GraphicsEngine(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight)
	: _d3d11(std::make_unique<D3D11Context>(hinst, hWnd, clientWidth, clientHeight))
	, _renderState(std::make_unique<RenderStates>(_d3d11->Divice()))
	, _font(std::make_unique<Font>(_d3d11->Divice(), _d3d11->DiviceContext(), _renderState->Solid(), _renderState->_normalDSS, FontType::gulima9k))
	, _grid(std::make_unique<Grid>(_d3d11->Divice(), _d3d11->DiviceContext(), _renderState->WireFrame()))
{

}

ge::GraphicsEngine::~GraphicsEngine()
{
}

void ge::GraphicsEngine::Initialize()
{

}

void ge::GraphicsEngine::Update(float deltaTime)
{
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
}
