#include "GraphicsEngine.h"
#include "D3D11Context.h"
#include "RenderStates.h"
#include "Font.h"
#include "FontType.h"
#include "Camera3D.h"

// Mesh Obj
#include "Grid.h"

#include <cassert>

ge::GraphicsEngine::GraphicsEngine(HINSTANCE& hinst, HWND hWnd, int clientWidth, int clientHeight)
	: _d3d11(std::make_unique<D3D11Context>(hinst, hWnd, clientWidth, clientHeight))
	, _renderState(std::make_unique<RenderStates>(_d3d11->Divice()))
	, _font(std::make_unique<Font>(_d3d11->Divice(), _d3d11->DiviceContext(), _renderState->Solid(), _renderState->_normalDSS, FontType::gulima9k))
	, _grid(std::make_unique<Grid>(_d3d11->Divice(), _d3d11->DiviceContext(), _renderState->WireFrame()))
	, _camera(std::make_unique<Camera3D>())
    ,_hWnd(hWnd)
{
    // 카메라 초기화
    _camera->SetPosition(0.0f, 2.0f, -15.0f);
    _camera->LookAt(DirectX::XMFLOAT3(10.f, 10.f, 10.f), DirectX::XMFLOAT3(0.f, 0.f, 0.f),
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
    _grid->_transpose.SetTM(DirectX::XMMatrixIdentity(), _camera->View(), _camera->Proj());
    _grid->SetEyePosW(_camera->GetPosition());
    Keybord();
}

void ge::GraphicsEngine::BeginRender()
{
	_d3d11->BeginRender();
}

void ge::GraphicsEngine::Render()
{
	_font->DrawTest();
	_grid->Render();
    DrawStatus();
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

void ge::GraphicsEngine::DrawStatus()
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

void ge::GraphicsEngine::Keybord()
{
    // 카메라 제어
    float speed = 0.0001f;
    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
        speed = 0.002f;
    else
        speed = 0.0001f;
    if (GetAsyncKeyState('W') & 0x8000)
        _camera->Walk(10.0f * speed);
    if (GetAsyncKeyState('S') & 0x8000)
        _camera->Walk(-10.0f * speed);
    if (GetAsyncKeyState('A') & 0x8000)
        _camera->Strafe(-10.0f * speed);
    if (GetAsyncKeyState('D') & 0x8000)
        _camera->Strafe(10.0f * speed);
}

void ge::GraphicsEngine::OnMouseDown(WPARAM btnState, int x, int y)
{
    _lastMousePos = POINT{x, y};

    SetCapture(_hWnd);
}

void ge::GraphicsEngine::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void ge::GraphicsEngine::OnMouseMove(WPARAM btnState, int x, int y)
{
    if ((btnState & MK_LBUTTON) != 0)
    {
        // 픽셀 하나가 사분의 일(0.25) 도에 해당하도록 만듦
        float dx = DirectX::XMConvertToRadians(0.25f * static_cast<float>(x - _lastMousePos.x));
        float dy = DirectX::XMConvertToRadians(0.25f * static_cast<float>(y - _lastMousePos.y));

        _camera->Pitch(dy);
        _camera->RotateY(dx);
    }

    _lastMousePos = POINT{x, y};
}
