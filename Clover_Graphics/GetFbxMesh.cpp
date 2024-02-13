#include "GetFbxMesh.h"

#include "FbxLoader.h"
#include "IndexBuffer_mk2.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
GetFbxMesh::GetFbxMesh(EntityPtr entityPtr, loader::FbxLoader* fbxLoader, std::string file)
    : GetEntity(EntityPtr(entityPtr))
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd GetFbxMesh Component\n";
#endif // _DEBUG;
}

//////////////////////////////////////////////////////////////////////
void GetFbxMesh::SetIndexBuffer(model::Mesh& data)
{
    // 읽고 있는 메시의 정점 크기
    unsigned int idxCount = static_cast<unsigned int>(data.faces.size());

    auto ib = GetComponent<IndexBuffer_mk2>();

    // 읽고 있는 매시가 시작될 인덱스 숫자
    ib->_indexOffset.emplace_back(ib->_totalIndexCount);

    // 읽고 있는 메시가 가질 총 인덱스 수
    ib->_indexCount.emplace_back(3 * idxCount);

    // 전체 인덱스 수
    ib->_totalIndexCount += (3 * idxCount);

    for (unsigned int i = 0; i < idxCount; ++i)
    {
        ib->_indices.emplace_back(static_cast<WORD>(data.faces[i].indices[0]));
        ib->_indices.emplace_back(static_cast<WORD>(data.faces[i].indices[1]));
        ib->_indices.emplace_back(static_cast<WORD>(data.faces[i].indices[2]));
    }
}

} // namespace graphics