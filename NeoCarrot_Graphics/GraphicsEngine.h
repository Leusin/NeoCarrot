/// GraphicsEngine.h
///
///


#pragma once

#include "ForGraphics.h"

#include <memory>
#include <wrl.h>

namespace grahics
{
class D3D11Context;
class RenderStates;
class Font;
class Grid;
class Camera3D;

class GraphicsEngine
{
public:
    GraphicsEngine(HINSTANCE& hinst, HWND hWnd, int clientWidth, int clientHeight);
    ~GraphicsEngine();

    void Initialize();
    void Update(float deltaTime);
    void Finalize();

    void OnResize(int clientWidth, int clientHeight);
    void DrawStatus();

    void ImportData(const data::ForGraphics* info);

private:

    void BeginRender();
    void Render();
    void EndRender();

    ///  랜더링 부분
    std::unique_ptr<D3D11Context> _d3d11;
    std::unique_ptr<RenderStates> _renderState;
    std::unique_ptr<Font>         _font;

    // Mesh Obj
    std::unique_ptr<Grid> _grid;

    /// 카메라 부분
    std::unique_ptr<Camera3D> _camera;
    // 카메라 데이터

    data::ForGraphics _fromGameEngine;
};

} // namespace ge