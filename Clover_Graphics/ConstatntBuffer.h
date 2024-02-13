#pragma once

#include <directxmath.h>

namespace graphics
{
struct MatrixBufferType
{
    DirectX::XMMATRIX world;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projection;
};
}