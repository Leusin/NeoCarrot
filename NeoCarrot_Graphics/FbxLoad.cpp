#include "FbxLoad.h"

#include "FbxLoader.h"
#include "D3Devices.h"
#include "IndexBuffer_mk2.h"
#include "InputLayouts.h"
#include "VertexResource.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
FbxLoad::FbxLoad(EntityPtr entityPtr, loader::FbxLoader* fbxLoader, std::string file)
    : GetEntity(EntityPtr(entityPtr))
    , _devices{ GetComponent<graphics::D3Devices>() }
    , _indexBuffer{ GetComponent<graphics::IndexBuffer_mk2>() }
    , _vertexResource{ GetComponent<graphics::VertexResource<Pos>>() }
{
    assert(_devices && "FbxLoad �� D3Devices �� �ʿ����");
    assert(_vertexResource && "FbxLoad �� IndexBuffer_mk2 �� �ʿ����");
    assert(_indexBuffer && "FbxLoad �� VertexResource �� �ʿ����");

    std::vector<model::Mesh> mesh = fbxLoader->GetMeshAll(
        file.c_str());

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd FbxLoad Component\n";
#endif // _DEBUG;
}

void FbxLoad::Awake()
{
}

} // namespace graphics