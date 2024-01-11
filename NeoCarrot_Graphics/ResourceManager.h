#pragma once

namespace graphics
{

class D3D11Context;
class D3D11RenderStates;
class DXTKFont;

class ResourceManager
{
public:
    ResourceManager();

    void Initialize();

private:
    D3D11Context*      _d3d11;
    D3D11RenderStates* _renderState;
    DXTKFont*          _font;
};

} // namespace graphics