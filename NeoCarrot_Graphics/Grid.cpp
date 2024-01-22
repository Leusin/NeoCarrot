#include "Grid.h"
#include <d3d11.h>
#include <DirectXColors.h>
#include <d3dx11effect.h>
#include <fstream>
#include <vector>

graphics::Grid::Grid(ID3D11Device* d, ID3D11DeviceContext* dc, ID3D11RasterizerState* rs)
	: _d3dDevice(d)
	, _d3dImmediateContext(dc)
	, _renderstate(rs)
	, _eyePosW(0.0f, 0.0f, 0.0f)
{
	BuildGeometryBuffers();
	BuildFX();
	BuildVertexLayout();
}

graphics::Grid::~Grid()
{
}

void graphics::Grid::Render()
{

	// �ε������ۿ� ���ؽ����� ����
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	/// ������ ���ο� �������� ����̽� �Է� ���Ͽ� �ֱ�

	// ���� ���� ��ġ ����
	_d3dImmediateContext->IASetVertexBuffers(0, 1, _vb.GetAddressOf(), &stride, &offset);
	// �ε��� ���� ����
	_d3dImmediateContext->IASetIndexBuffer(
		_ib.Get(),
		DXGI_FORMAT_R32_UINT,	// �ε��� ����
		0);						// ������ ��

	// �Է� ��ġ ��ü ����
	_d3dImmediateContext->IASetInputLayout(_inputLayout.Get());
	_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// WVP TM���� ����
	DirectX::XMMATRIX worldViewProj = _transpose.GetWorldViewProj();
	_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	// ����������Ʈ
	_d3dImmediateContext->RSSetState(_renderstate);

	D3DX11_TECHNIQUE_DESC techDesc;
	_tech->GetDesc(&techDesc);

	// �����н���...
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		_tech->GetPassByIndex(p)->Apply(0, _d3dImmediateContext);

		// 20���� �ε����� �׸��带 �׸���.
		_d3dImmediateContext->DrawIndexed(40, 0, 0);
	}
}

void graphics::Grid::BuildGeometryBuffers()
{
	/// ���� ����

	Vertex vertices[100];
	for (int i = 0; i < 100; i++)
	{
		vertices[i].Pos = DirectX::XMFLOAT3((float)(i % 10) - 5.0f, 0.0f, (float)(i / 10) - 5.0f);
		vertices[i].Color = DirectX::XMFLOAT4((const float*)&DirectX::Colors::Orange);
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;			// ���� ũ��
	vbd.ByteWidth = sizeof(Vertex) * 100;		// ���۰� ���̴� ����
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���ε� �Ǵ� ���
	vbd.CPUAccessFlags = 0;						// CPU�� ���ۿ� �����ϴ� ��
	vbd.MiscFlags = 0;							// ��Ÿ �÷���
	vbd.StructureByteStride = 0;				// ������ ���� ũ��

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices; // �ʱ�ȭ ������ ������

	_d3dDevice->CreateBuffer(
		&vbd,						// ������ ���۸� ��� ����
		&vinitData,			// ���۸� �ʱ�ȭ�ϴµ� ����� �ڷ�
		_vb.GetAddressOf());		// ���� ����


	/// �ε��� ����

	// �ε��� ���۸� �����Ѵ�.
	// ���� 40���� ������ ��Ÿ������ �ߴ�.
	UINT indices[40];
	for (int i = 0; i < 10; i++)
	{
		indices[i * 2] = i;
		indices[i * 2 + 1] = i + 90;
	}

	for (int i = 0; i < 10; i++)
	{
		indices[20 + (i * 2)] = i * 10;
		indices[20 + (i * 2) + 1] = i * 10 + 9;
	}

	// �ε��� ���۸� �����ϴ� ����ü
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 40;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// �ε��� ���۸� �ʱ�ȭ�� �ڷ� ����
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;

	// �ε��� ���� ���� 
	_d3dDevice->CreateBuffer(&ibd,
		&iinitData,
		_ib.GetAddressOf());
}

void graphics::Grid::BuildFX()
{
	// ���� ������ ���
	const TCHAR* pathName{ L"../NeoCarrot_Graphics/FX" };
	const TCHAR* fileName{ L"color.fxo" };
	std::wstring fullPath = std::wstring(pathName) + L"\\" + fileName;
	std::ifstream fin(fullPath, std::ios::binary);

	if (!fin)
	{
		MessageBox(0, L"cso Not found.", 0, 0);
	}

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	D3DX11CreateEffectFromMemory(
		&compiledShader[0],		// �����ϵ� ȿ�� ������ Blob
		size,					// Blob �� ����
		0,						// ����Ʈ �÷���
		_d3dDevice,					// ����̽� ������
		_fx.GetAddressOf());					// ���� ���� ����Ʈ �������̽� �ּ�

	_tech = _fx->GetTechniqueByName("ColorTech");
	_fxWorldViewProj = _fx->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void graphics::Grid::BuildVertexLayout()
{
	/// ���� �Է°� ��ġ

	// �Է� ���̾ƾƿ� ����
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	D3DX11_PASS_DESC passDesc;
	_tech->GetPassByIndex(0)->GetDesc(&passDesc);

	_d3dDevice->CreateInputLayout(vertexDesc, 2,
		passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize,
		_inputLayout.GetAddressOf());
}
