/// MeshLoader.h : ControlPoint, Polgon, Material 관련 데이터를 다루는 클래스 입니다.
/// 
/// 2023-12-29


#pragma once

#include "../Bunny_Common/Mesh.h"
#include "../Bunny_Common/Vector3.h"

#include <fbxsdk.h>
#include <vector>

namespace loader
{

class MeshLoader
{
public:
	MeshLoader(FbxManager* manager);

	model::Mesh       GetMesh(size_t i);
    std::vector<model::Mesh> GetMeshAll();
	size_t GetMeshSize();

	void LoadMesh(FbxNode* node);

private:
	// 정점 데이터
	void LoadControlsPoints(FbxMesh* mesh);
	// 폴리곤 데이터
	void LoadPolygons(FbxMesh* mesh);
	// 머터리얼 데이터

	//void DisplayMaterial(FbxMesh* mesh);
	//void DisplayTexture(FbxGeometry* mesh);
	//void DisplayMaterialConnections(FbxGeometry* mesh);
	//void DisplayLink(FbxGeometry* mesh);
	//void DisplayShape(FbxGeometry* mesh);
	//void DisplayCache(FbxGeometry* mesh);

	void IndicesSplit();

	/// <summary>
	///  외부에서 받아 쓰는 Fbx Manager
	/// </summary>
	FbxManager* _manager{ nullptr };

	std::vector<math::Vector3<float>> _ControlPositions;

	/// <summary>
	/// 최종적으로 외부로 내보낼 데이터
	/// </summary>
    std::vector<model::Mesh> _meshes;
};
}