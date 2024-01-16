/// GraphicsEngine.h
///
///


#pragma once

#include "ForGraphics.h"

#include <memory>
#include <wrl.h>

namespace graphics
{
class D3D11Context_mk2;
class DXTKFont;
class Camera3D;
class ModelManager;

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

    void BeginRender();
    void Render();
    void EndRender();

private:
    // 리소스
    std::unique_ptr<D3D11Context_mk2> _d3d11context;
    std::unique_ptr<DXTKFont>         _font;

    // 메시
    std::unique_ptr<ModelManager> _modelManager;

    /// 카메라
    std::unique_ptr<Camera3D> _camera;

    // 외부 데이터
    data::ForGraphics _fromGameEngine;
};

} // namespace ge