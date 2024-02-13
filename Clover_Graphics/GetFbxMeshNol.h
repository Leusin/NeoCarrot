/// FbxLoader ������Ʈ�� �ٸ��� �޽ø� �������� Ŭ����
///
/// 2024-01-23


#pragma once

#include "FbxLoader.h"
#include "GetFbxMesh.h"
#include "VertexBufferStruct.h"

#include <string>

namespace graphics
{

class GetFbxMeshNol: public GetFbxMesh
{
private:
    struct PosNol: public Pos, public Nol
    {
    };

public:
    GetFbxMeshNol(EntityPtr entityPtr, loader::FbxLoader* fbxLoader, std::string file);

    void SetVertexBuffer(model::Mesh& data) override;
};

} // namespace graphics