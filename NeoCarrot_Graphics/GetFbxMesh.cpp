#include "GetFbxMesh.h"

#include "FbxLoader.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
GetFbxMesh::GetFbxMesh(loader::FbxLoader* fbxLoader, std::string file)
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd GetFbxMesh Component\n";
#endif // _DEBUG;

    _meshes = fbxLoader->GetMeshAll(file.c_str());
}

} // namespace graphics