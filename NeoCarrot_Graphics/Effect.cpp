#include "Effect.h"

#include "D3Devices.h"
#include "Transpose.h"

#include <d3dcompiler.h>
#include <fstream>
#include <vector>

#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
Effect::Effect(EntityPtr entityPtr, std::wstring fileName) :
GetEntity(EntityPtr(entityPtr)),
_fileName(fileName),
_d3device{GetComponent<graphics::D3Devices>()}
{
    assert(_d3device && "Effect ���� D3Devices �� ã�� �� ����");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Effect Component\n";
#endif // _DEBUG
}

void Effect::Awake()
{
    AwakeReadFile();
    AwakeGetTechniqueByName();
}

void Effect::Update(float dt)
{
    UpdateSetWorldViewProj();
}

bool Effect::CompileFromFile()
{
    Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob{nullptr};
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{nullptr};

    HRESULT hr = D3DCompileFromFile(_fileName.c_str(),         // HLSL ���� ���
                                    nullptr,                   // ��ũ�� ���� (������ nullptr)
                                    nullptr,                   // include ���� (������ nullptr)
                                    "main",                    // ������ �Լ� �̸�
                                    "ps_5_0",                  // �������� ��������
                                    0,                         // �÷��� (������ 0)
                                    0,                         // �÷��� (������ 0)
                                    shaderBlob.GetAddressOf(), // �����ϵ� ���̴� �ڵ带 ������ ����
                                    errorBlob.GetAddressOf()   // ������ ���� �޽����� ������ ����
    );

    // ������ ��� Ȯ��
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
            errorBlob->Release();
        }
        // ���� ó��
        // ...

        return false;
    }

    return true;
}

void Effect::AwakeGetTechniqueByName()
{

    _tech            = _fx->GetTechniqueByName("ColorTech");
    _fxWorldViewProj = _fx->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void Effect::UpdateSetWorldViewProj()
{
    auto worldViewProj = GetComponent<Transpose>()->WorldViewProj();
    _fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
}

void Effect::AwakeReadFile()
{
    std::ifstream fin(_fileName, std::ios::binary);

    if (!fin)
    {
        if (CompileFromFile())
            MessageBox(0, L"������ ã�� �� ������.", 0, 0);
    }

    fin.seekg(0, std::ios_base::end);
    int size = (int)fin.tellg();
    fin.seekg(0, std::ios_base::beg);
    std::vector<char> compiledShader(size);

    fin.read(&compiledShader[0], size);
    fin.close();

    HRESULT result = D3DX11CreateEffectFromMemory(&compiledShader[0],     // �����ϵ� ȿ�� ������ Blob
                                                  size,                   // Blob �� ����
                                                  0,                      // ����Ʈ �÷���
                                                  _d3device->GetDevice(), // ����̽� ������
                                                  _fx.GetAddressOf()); // ���� ���� ����Ʈ �������̽� �ּ�

    assert(_fx);
}

void Effect::GetTechniqueDesc(D3DX11_TECHNIQUE_DESC* des)
{
    _tech->GetDesc(des);
}

} // namespace graphics