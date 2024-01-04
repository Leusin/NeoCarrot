#include "Transpose.h"
#include <directXMath.h>

ge::Transpose::Transpose()
{
	DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();
	XMStoreFloat4x4(&_world, I);
	XMStoreFloat4x4(&_view, I);
	XMStoreFloat4x4(&_proj, I);
}

ge::Transpose::~Transpose()
{
}

DirectX::XMMATRIX ge::Transpose::GetWorld()
{
	return  DirectX::XMLoadFloat4x4(&_world);
}

DirectX::XMMATRIX ge::Transpose::GetView()
{
	return  DirectX::XMLoadFloat4x4(&_view);
}

DirectX::XMMATRIX ge::Transpose::GetProj()
{
	return  DirectX::XMLoadFloat4x4(&_proj);
}

void ge::Transpose::SetWorld(const DirectX::XMMATRIX& w)
{
	DirectX::XMStoreFloat4x4(&_world, w);
}

void ge::Transpose::SetView(const DirectX::XMMATRIX& v)
{
	DirectX::XMStoreFloat4x4(&_view, v);
}

void ge::Transpose::SetProj(const DirectX::XMMATRIX& p)
{
	DirectX::XMStoreFloat4x4(&_proj, p);
}

void ge::Transpose::SetTM(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj)
{
	DirectX::XMStoreFloat4x4(&_world, world);
	DirectX::XMStoreFloat4x4(&_view, view);
	DirectX::XMStoreFloat4x4(&_proj, proj);
}

DirectX::XMMATRIX ge::Transpose::WorldViewProj()
{
	return GetWorld() * GetView() * GetProj();
}
