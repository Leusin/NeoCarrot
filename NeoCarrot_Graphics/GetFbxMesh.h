/// FbxLoader 컴포넌트와 다르게 메시만 가져오는 클래스
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