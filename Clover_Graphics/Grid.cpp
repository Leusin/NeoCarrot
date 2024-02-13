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

	// 인덱스버퍼와 버텍스버퍼 셋팅
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	/// 파이프 라인에 묶기위해 디바이스 입력 슬록에 넣기

	// 정점 버퍼 장치 묶기
	_d3dImmediateContext->IASetVertexBuffers(0, 1, _vb.GetAddressOf(), &stride, &offset);
	// 인덱스 버퍼 묶기
	_d3dImmediateContext->IASetIndexBuffer(
		_ib.Get(),
		DXGI_FORMAT_R32_UINT,	// 인덱스 형식
		0);						// 오프셋 값

	// 입력 배치 객체 셋팅
	_d3dImmediateContext->IASetInputLayout(_inputLayout.Get());
	_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// WVP TM등을 셋팅
	DirectX::XMMATRIX worldViewProj = _transpose.GetWorldViewProj();
	_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	// 렌더스테이트
	_d3dImmediateContext->RSSetState(_renderstate);

	D3DX11_TECHNIQUE_DESC techDesc;
	_tech->GetDesc(&techDesc);

	// 랜더패스는...
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		_tech->GetPassByIndex(p)->Apply(0, _d3dImmediateContext);

		// 20개의 인덱스로 그리드를 그린다.
		_d3dImmediateContext->DrawIndexed(40, 0, 0);
	}
}

void graphics::Grid::BuildGeometryBuffers()
{
	/// 정점 버퍼

	Vertex vertices[100];
	for (int i = 0; i < 100; i++)
	{
		vertices[i].Pos = DirectX::XMFLOAT3((float)(i % 10) - 5.0f, 0.0f, (float)(i / 10) - 5.0f);
		vertices[i].Color = DirectX::XMFLOAT4((const float*)&DirectX::Colors::Orange);
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;			// 버퍼 크기
	vbd.ByteWidth = sizeof(Vertex) * 100;		// 버퍼가 쓰이는 형식
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 바인딩 되는 방법
	vbd.CPUAccessFlags = 0;						// CPU가 버퍼에 접근하는 법
	vbd.MiscFlags = 0;							// 기타 플래그
	vbd.StructureByteStride = 0;				// 구조적 버퍼 크기

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices; // 초기화 데이터 포인터

	_d3dDevice->CreateBuffer(
		&vbd,						// 생성할 버퍼를 담는 변수
		&vinitData,			// 버퍼를 초기화하는데 사용할 자료
		_vb.GetAddressOf());		// 버퍼 설정


	/// 인덱스 버퍼

	// 인덱스 버퍼를 생성한다.
	// 역시 40개의 라인을 나타내도록 했다.
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

	// 인덱스 버퍼를 서술하는 구조체
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 40;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// 인덱스 버퍼를 초기화할 자료 지정
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;

	// 인덱스 버퍼 생성 
	_d3dDevice->CreateBuffer(&ibd,
		&iinitData,
		_ib.GetAddressOf());
}

void graphics::Grid::BuildFX()
{
	// 실행 파일의 경로
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
		&compiledShader[0],		// 컴파일된 효과 데이터 Blob
		size,					// Blob 의 길이
		0,						// 이펙트 플래그
		_d3dDevice,					// 디바이스 포인터
		_fx.GetAddressOf());					// 새로 만든 이펙트 인터페이스 주소

	_tech = _fx->GetTechniqueByName("ColorTech");
	_fxWorldViewProj = _fx->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void graphics::Grid::BuildVertexLayout()
{
	/// 정점 입력과 배치

	// 입력 레이아아웃 서술
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
