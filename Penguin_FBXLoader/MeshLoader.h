/// MeshLoader.h : ControlPoint, Polgon, Material ���� �����͸� �ٷ�� Ŭ���� �Դϴ�.
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
	// ���� ������
	void LoadControlsPoints(FbxMesh* mesh);
	// ������ ������
	void LoadPolygons(FbxMesh* mesh);
	// ���͸��� ������

	//void DisplayMaterial(FbxMesh* mesh);
	//void DisplayTexture(FbxGeometry* mesh);
	//void DisplayMaterialConnections(FbxGeometry* mesh);
	//void DisplayLink(FbxGeometry* mesh);
	//void DisplayShape(FbxGeometry* mesh);
	//void DisplayCache(FbxGeometry* mesh);

	void IndicesSplit();

	/// <summary>
	///  �ܺο��� �޾� ���� Fbx Manager
	/// </summary>
	FbxManager* _manager{ nullptr };

	std::vector<math::Vector3<float>> _ControlPositions;

	/// <summary>
	/// ���������� �ܺη� ������ ������
	/// </summary>
    std::vector<model::Mesh> _meshes;
};
}