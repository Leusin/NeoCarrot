/// FbxLoader ������Ʈ�� �ٸ��� �޽ø� �������� Ŭ����
///
/// 2024-01-23


#pragma once

#include "GetFbxMesh.h"

#include <string>
namespace loader{class FbxLoader;}

namespace graphics
{

class GetFbxMeshNol: public GetFbxMesh
{
public:
    GetFbxMeshNol(EntityPtr entityPtr, loader::FbxLoader* fbxLoader, std::string file);

    void SetVertexBuffer(model::Mesh& data) override;
};

} // namespace graphics