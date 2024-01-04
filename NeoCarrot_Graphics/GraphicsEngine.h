/// GraphicsEngine.h
///
///


#pragma once

#include <memory>
#include <wrl.h>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;


namespace ge
{
class D3D11Context;
class RenderStates;
class Font;
class Grid;
class Camera3D;

class GraphicsEngine
{
public:
    GraphicsEngine(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight);
    ~GraphicsEngine();

    void Initialize();
    void Update(float deltaTime);
    void BeginRender();
    void Render();
    void Finalize();
    void EndRender();

    void OnResize(int clientWidth, int clientHeight);

private:
    ///  랜더링 부분
    std::unique_ptr<D3D11Context> _d3d11;
    std::unique_ptr<RenderStates> _renderState;
    std::unique_ptr<Font>         _font;

    // Mesh Obj
    std::unique_ptr<Grid> _grid;

    /// 카메라 부분
    std::unique_ptr<Camera3D> _camera;
    // 카메라 데이터
};

} // namespace ge