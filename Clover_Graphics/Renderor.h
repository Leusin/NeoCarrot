/// Renderor.h
///


#pragma once

#include "D3D11Context.h"
#include "Camera.h"
#include "Model.h"

// 셰이더
#include "ColorShader.h"
#include "TextureShader.h"

//#include <memory>
#include <wrl.h>

namespace graphics
{

class D3D11Renderor
{
public:
    D3D11Renderor(HINSTANCE& hinst, HWND hWnd, int clientWidth, int clientHeight);
    D3D11Renderor(const D3D11Renderor&);
    ~D3D11Renderor();

    void Initialize();
    void Update(float deltaTime);
    void Finalize();

    void OnResize(int clientWidth, int clientHeight);

private:
    void Render();

    std::unique_ptr<Camera> _camera{ nullptr };
    std::unique_ptr<D3D11Context> _d3d11{ nullptr };

    std::unique_ptr<Model> _model{ nullptr };
    //std::unique_ptr<ColorShader> _colorShader{ nullptr };
    std::unique_ptr<TextureShader> _textureShader{ nullptr };

    //std::unique_ptr<DXTKFont>         _font;

    // 메시
    //std::unique_ptr<ModelManager> _modelManager;

    // 카메라
    //std::unique_ptr<Camera3D> _camera;

    // 외부 데이터
    //data::ForGraphics _fromGameEngine;

};

} // namespace ge