/// FbxLoader.h
/// - FbxScene �� FbxManager ��ü�� �����մϴ�.
/// - Scene ���� ��Ÿ ������ �����ϴ� ��ü���� �����մϴ�
///
/// 2023-12-29
///

#pragma once

#if _DEBUG
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/libfbxsdk-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/libxml2-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/debug/zlib-md.lib")
#else
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/libfbxsdk-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/libxml2-md.lib")
#pragma comment(lib, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release/zlib-md.lib")
#endif

#include "../Bunny_Common/Mesh.h"

#include <fbxsdk.h>
//#include <C:\Program Files\Autodesk\FBX\FBX SDK\2020.3.4\include\fbxsdk.h>
#include <vector>
#include <memory>

namespace loader
{
// ���� ����
class MeshLoader;

// ����
class FbxLoader
{
public:
    FbxLoader();
    ~FbxLoader();

    model::Mesh             GetMesh(const char* file, size_t i);
    std::vector<model::Mesh> GetMeshAll(const char* file);
    size_t            GetMeshSize(const char* file);

    // ������. �Ž� ��� �� �� ó���� �޽ø� �е��� �Ѵ�.
    void LoadAMeshContent(const char* file);

private:
    void LoadFbxFile(const char* file);
    bool CreateFbxScene(const char* file);
    void LoadContent();
    void LoadContent(FbxNode* node);

    void DisplayTarget(FbxNode* pNode);
    void DisplayTransformPropagation(FbxNode* pNode);
    void DisplayGeometricTransform(FbxNode* pNode);
    void DisplayMetaData(FbxScene* pScene);

    // FBX ��ü
    FbxScene* _scene{nullptr};
    FbxManager* _manager{nullptr};

    // Loader ��ü
    std::unique_ptr <MeshLoader> _meshLoader{nullptr};
};

} // namespace loader