#include "Effect.h"

#include "D3Devices.h"
#include "Transpose.h"

#include <fstream>
#include <vector>
#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
Effect::Effect(EntityPtr entityPtr, std::wstring fileName) 
    : GetEntity(EntityPtr(entityPtr))
    , _fileName(fileName)
    , _d3device{GetComponent<graphics::D3Devices>()}
{
    assert(_d3device && "Effect 에서 D3Devices 를 찾을 수 없음");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Effect Component\n";
#endif // _DEBUG
}

void Effect::Awake()
{

    std::ifstream fin(_fileName, std::ios::binary);

    if (!fin)
    {
        MessageBox(0, L"파일을 찾을 수 없으센.", 0, 0);
    }

    fin.seekg(0, std::ios_base::end);
    int size = (int)fin.tellg();
    fin.seekg(0, std::ios_base::beg);
    std::vector<char> compiledShader(size);

    fin.read(&compiledShader[0], size);
    fin.close();

    D3DX11CreateEffectFromMemory(&compiledShader[0],     // 컴파일된 효과 데이터 Blob
                                 size,                   // Blob 의 길이
                                 0,                      // 이펙트 플래그
                                 _d3device->GetDevice(), // 디바이스 포인터
                                 _fx.GetAddressOf());    // 새로 만든 이펙트 인터페이스 주소

    _tech            = _fx->GetTechniqueByName("ColorTech");
    _fxWorldViewProj = _fx->GetVariableByName("gWorldViewProj")->AsMatrix();

}

void Effect::Update(float dt)
{
    SetWorldViewProj();
}

void Effect::SetWorldViewProj()
{
    auto worldViewProj = GetComponent<Transpose>()->WorldViewProj();
    _fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
}

void Effect::GetTechniqueDesc(D3DX11_TECHNIQUE_DESC* des)
{
    _tech->GetDesc(des);
}

} // namespace graphics