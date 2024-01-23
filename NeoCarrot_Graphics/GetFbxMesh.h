/// FbxLoader ������Ʈ�� �ٸ��� �޽ø� �������� Ŭ����
///
/// 2024-01-23


#pragma once

#include "IComponent.h"
#include "Mesh.h"

#include <string>
namespace loader{class FbxLoader;}

namespace graphics
{

class GetFbxMesh: public core::IComponent
{
public:
    GetFbxMesh(loader::FbxLoader* fbxLoader, std::string file);

    std::vector<model::Mesh> _meshes;
};

} // namespace graphics