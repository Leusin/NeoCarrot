#include "ResourceManager.h"

#include "D3D11Context.h"
#include "D3D11RenderStates.h"
#include "DXTKFont.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

ResourceManager::ResourceManager()
{
#ifdef _DEBUG
    std::cout << "\tResourceManager Constructed\n";
#endif // _DEBUG
};

void ResourceManager::Initialize()
{

}

} // namespace graphics