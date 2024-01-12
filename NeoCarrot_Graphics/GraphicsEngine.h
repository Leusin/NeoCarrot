/// GraphicsEngine.h
///
///


#pragma once

#include "ForGraphics.h"

#include <memory>
#include <wrl.h>

namespace graphics
{
class D3D11Context;
class D3D11RenderStates;
class DXTKFont;
class Grid;
class Camera3D;

class ModelManager;
class ResourceManager;

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

    //  ���ҽ���
    std::unique_ptr<D3D11Context> _d3d11;
    std::unique_ptr<D3D11RenderStates> _renderState;
    std::unique_ptr<DXTKFont>         _font;
    
    /// ���ҽ� �Ŵ���
    std::unique_ptr<ResourceManager> _resourceManager;

    // Mesh Obj
    std::unique_ptr<Grid> _grid;
    std::unique_ptr<ModelManager> _modelManager;

    /// ī�޶� �κ�
    std::unique_ptr<Camera3D> _camera;
    // ī�޶� ������

    data::ForGraphics _fromGameEngine;
};

} // namespace ge