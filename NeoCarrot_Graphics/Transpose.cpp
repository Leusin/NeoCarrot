#include "Transpose.h"
#include <directXMath.h>

graphics::Transpose::Transpose()
{
	DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();
	XMStoreFloat4x4(&_world, I);
	XMStoreFloat4x4(&_view, I);
	XMStoreFloat4x4(&_proj, I);
}

graphics::Transpose::~Transpose()
{
}

DirectX::XMMATRIX graphics::Transpose::GetWorld()
{
	return  DirectX::XMLoadFloat4x4(&_world);
}

DirectX::XMMATRIX graphics::Transpose::GetView()
{
	return  DirectX::XMLoadFloat4x4(&_view);
}

DirectX::XMMATRIX graphics::Transpose::GetProj()
{
	return  DirectX::XMLoadFloat4x4(&_proj);
}

void graphics::Transpose::SetWorld(const DirectX::XMMATRIX& w)
{
	DirectX::XMStoreFloat4x4(&_world, w);
}

void graphics::Transpose::SetView(const DirectX::XMMATRIX& v)
{
	DirectX::XMStoreFloat4x4(&_view, v);
}

void graphics::Transpose::SetProj(const DirectX::XMMATRIX& p)
{
	DirectX::XMStoreFloat4x4(&_proj, p);
}

void graphics::Transpose::SetTM(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj)
{
	DirectX::XMStoreFloat4x4(&_world, world);
	DirectX::XMStoreFloat4x4(&_view, view);
	DirectX::XMStoreFloat4x4(&_proj, proj);
}

DirectX::XMMATRIX graphics::Transpose::WorldViewProj()
{
	return GetWorld() * GetView() * GetProj();
}
