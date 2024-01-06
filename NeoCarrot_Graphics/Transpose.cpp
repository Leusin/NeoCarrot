#include "Transpose.h"
#include <directXMath.h>

grahics::Transpose::Transpose()
{
	DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();
	XMStoreFloat4x4(&_world, I);
	XMStoreFloat4x4(&_view, I);
	XMStoreFloat4x4(&_proj, I);
}

grahics::Transpose::~Transpose()
{
}

DirectX::XMMATRIX grahics::Transpose::GetWorld()
{
	return  DirectX::XMLoadFloat4x4(&_world);
}

DirectX::XMMATRIX grahics::Transpose::GetView()
{
	return  DirectX::XMLoadFloat4x4(&_view);
}

DirectX::XMMATRIX grahics::Transpose::GetProj()
{
	return  DirectX::XMLoadFloat4x4(&_proj);
}

void grahics::Transpose::SetWorld(const DirectX::XMMATRIX& w)
{
	DirectX::XMStoreFloat4x4(&_world, w);
}

void grahics::Transpose::SetView(const DirectX::XMMATRIX& v)
{
	DirectX::XMStoreFloat4x4(&_view, v);
}

void grahics::Transpose::SetProj(const DirectX::XMMATRIX& p)
{
	DirectX::XMStoreFloat4x4(&_proj, p);
}

void grahics::Transpose::SetTM(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj)
{
	DirectX::XMStoreFloat4x4(&_world, world);
	DirectX::XMStoreFloat4x4(&_view, view);
	DirectX::XMStoreFloat4x4(&_proj, proj);
}

DirectX::XMMATRIX grahics::Transpose::WorldViewProj()
{
	return GetWorld() * GetView() * GetProj();
}
