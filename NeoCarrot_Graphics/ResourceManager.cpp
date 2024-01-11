#include "ResourceManager.h"

#include "D3D11Context.h"
#include "D3D11RenderStates.h"
#include "DXTKFont.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
ResourceManager::ResourceManager(D3D11Context* d3d11, D3D11RenderStates* renderState, DXTKFont* font) :
_d3d11(d3d11),
_renderState(renderState),
_font(font)
{
#ifdef _DEBUG
    std::cout << "\tResourceManager Constructed\n";
#endif // _DEBUG
};

void ResourceManager::Initialize()
{
}

} // namespace graphics