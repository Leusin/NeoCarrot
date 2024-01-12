#include "Effect.h"

#include "D3Device.h"

#include <fstream>
#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
Effect::Effect(EntityPtr entityPtr, std::wstring fileName) :
_fileName(fileName),
_entity{EntityPtr(entityPtr)},
_d3device{_entity.lock()->GetComponent<graphics::D3Device>()}
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Effect Component\n";
#endif // _DEBUG
}

void Effect::Awake()
{

    std::ifstream fin(_fileName, std::ios::binary);

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

    D3DX11CreateEffectFromMemory(&compiledShader[0],     // �����ϵ� ȿ�� ������ Blob
                                 size,                   // Blob �� ����
                                 0,                      // ����Ʈ �÷���
                                 _d3device->GetDevice(), // ����̽� ������
                                 _fx.GetAddressOf());    // ���� ���� ����Ʈ �������̽� �ּ�

    _tech            = _fx->GetTechniqueByName("ColorTech");
    _fxWorldViewProj = _fx->GetVariableByName("gWorldViewProj")->AsMatrix();

#ifdef _DEBUG
    std::cout << "\t\t\t\t\tAdd Effect D3Device Awake\n";
#endif // _DEBUG;
}

} // namespace graphics