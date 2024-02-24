/// Renderor.h
///


#pragma once

#include "D3D11Context.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"

// ���̴�
#include "ColorShader.h"
#include "TextureShader.h"
#include "LightShader.h"

// ���۵� ����
#include "DeferredBuffers.h"
#include "DeferredShader.h"

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
    void RenderSceneToTexture();

    int _width;
    int _height;

    std::unique_ptr<D3D11Context> _d3d11{ nullptr };
    std::unique_ptr<Camera> _camera{ nullptr };
    std::unique_ptr<Light> _light{ nullptr };
    std::unique_ptr<Model> _model{ nullptr };

    //std::unique_ptr<ColorShader> _colorShader{ nullptr };
    std::unique_ptr<TextureShader> _textureShader{ nullptr };
    std::unique_ptr<LightShader> _lightShader{ nullptr };

    std::unique_ptr<DeferredBuffers> _deferredBuffer{ nullptr };
    std::unique_ptr<DeferredShader> _deferredShader{ nullptr };

    //std::unique_ptr<DXTKFont>         _font;

    // �޽�
    //std::unique_ptr<ModelManager> _modelManager;

    // ī�޶�
    //std::unique_ptr<Camera3D> _camera;

    // �ܺ� ������
    //data::ForGraphics _fromGameEngine;

};

} // namespace ge