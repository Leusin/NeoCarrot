#include "MeshLoader.h"

#include <cassert>

loader::MeshLoader::MeshLoader(FbxManager* manager) : _manager(manager)
{
    assert(_manager);
}

model::Mesh loader::MeshLoader::GetMesh(size_t i)
{
    assert(i < _meshes.size());

    return _meshes[i];
}

std::vector<model::Mesh> loader::MeshLoader::GetMeshAll()
{
    return _meshes;
}

size_t loader::MeshLoader::GetMeshSize()
{
    return _meshes.size();
}

// Poligon�� ������ Vertex �� �̷���� �ִ�.
// ���� fbx ������ ���� Face �� �ﰢ���� �ƴϴ���
// �Ʒ� �Լ��� ��ġ�� �ﰢ���� �ȴ�.
void loader::MeshLoader::LoadMesh(FbxNode* node)
{

    // Fbx Mesh ����
    FbxMesh* mesh = (FbxMesh*)node->GetNodeAttribute();
    if (mesh->RemoveBadPolygons() < 0)
        return;

    // ���ο� �޽� �߰�
    _meshes.emplace_back(model::Mesh());

    // ������ ��� ���� �ﰢ�� ���������� �ٲ�
    {
        FbxGeometryConverter geoConvertor{_manager};
        mesh = static_cast<FbxMesh*>(geoConvertor.Triangulate(mesh, true));
        if (!mesh || mesh->RemoveBadPolygons() < 0)
            return;
    }

    FBXSDK_printf("Mesh Name: %s\n", (char*)node->GetName());
    //LoadControlsPoints(mesh);

    // �޽� �Ľ��� �̷������.
    LoadPolygons(mesh);

    // DisplayMaterialMapping(mesh);

    // DisplayTexture(mesh);

    /// ------------------------------

    // ��Ÿ �߰��Ҹ��� mesh ������
    // DisplayMaterial(lMesh);
    // DisplayMaterialConnections(lMesh);
    // DisplayLink(lMesh);
    // DisplayShape(lMesh);
    // DisplayCache(lMesh);

    /// ------------------------------

    // --------
    // �Ľ��� ������ ����
    // --------

    // �� ����� Fbx Mesh  ����
    mesh->Destroy();
}

void loader::MeshLoader::LoadControlsPoints(FbxMesh* mesh)
{
    int         i, controlPointsCount = mesh->GetControlPointsCount();
    FbxVector4* cntrolPoints = mesh->GetControlPoints();

    // ������ ������
    _ControlPositions.clear();

    FBXSDK_printf("    Control Points\n");

    for (i = 0; i < controlPointsCount; i++)
    {
        FBXSDK_printf("        Control Point %d\n", i);
        FBXSDK_printf("            Coordinates: %f, %f, %f\n", cntrolPoints[i][0], cntrolPoints[i][1], cntrolPoints[i][2]);

        _ControlPositions.emplace_back(static_cast<float>(cntrolPoints[i][0]),
                                       static_cast<float>(cntrolPoints[i][1]),
                                       static_cast<float>(cntrolPoints[i][2]));

        for (int j = 0; j < mesh->GetElementNormalCount(); j++)
        {
            FbxGeometryElementNormal* eNormals = mesh->GetElementNormal(j);
            if (eNormals->GetMappingMode() == FbxGeometryElement::eByControlPoint)
            {
                char header[100];
                FBXSDK_sprintf(header, 100, "            Normal Vector: ");
                if (eNormals->GetReferenceMode() == FbxGeometryElement::eDirect)
                    FBXSDK_printf("        %s %f, %f, %f\n",
                                  header,
                                  eNormals->GetDirectArray().GetAt(i)[0],
                                  eNormals->GetDirectArray().GetAt(i)[1],
                                  eNormals->GetDirectArray().GetAt(i)[2]);
            }
        }
    }

    FBXSDK_printf("\n");
}

void loader::MeshLoader::LoadPolygons(FbxMesh* mesh)
{
    int         i, j, polygonCount = mesh->GetPolygonCount();
    FbxVector4* controlPoints = mesh->GetControlPoints();
    char        header[100];

    // Fbx�� Poligon �� ImpFace �� ����.
    // ���� _meshFace �� ����� Face ũ�⸸ŭ ����ش�.

    _meshes.back().faces.resize(polygonCount);
    _meshes.back().vertices.resize(polygonCount * 3);

    FBXSDK_printf("    Polygons\n");

    int vertexId{0};

    for (i = 0; i < polygonCount; i++)
    {
        FBXSDK_printf("        Polygon %d\n", i);
        int l;

        for (l = 0; l < mesh->GetElementPolygonGroupCount(); l++)
        {
            FbxGeometryElementPolygonGroup* ePolgrp = mesh->GetElementPolygonGroup(l);
            switch (ePolgrp->GetMappingMode())
            {
                case FbxGeometryElement::eByPolygon:
                    if (ePolgrp->GetReferenceMode() == FbxGeometryElement::eIndex)
                    {
                        FBXSDK_sprintf(header, 100, "        Assigned to group: ");
                        int polyGroupId = ePolgrp->GetIndexArray().GetAt(i);
                        FBXSDK_printf("%s %d\n", header, polyGroupId);
                        break;
                    }
                default:
                    // any other mapping modes don't make sense
                    FBXSDK_printf("        \"unsupported group assignment\"\n");
                    break;
            }
        }

        // �������� ������� ������ 3 �̴�.
        int polygonSize = mesh->GetPolygonSize(i);

        for (j = 0; j < polygonSize; j++)
        {
            /// ----------------
            /// Vertex Position
            /// ----------------

            // �������� ��� ������ �غ��Ѵ�.
            FbxVector4 localPosition;

            int controlPointIndex = mesh->GetPolygonVertex(i, j);
            if (controlPointIndex < 0)
            {
                FBXSDK_printf("            Coordinates: Invalid index found!\n");
                continue;
            }
            else
            {
                localPosition = controlPoints[controlPointIndex];
                FBXSDK_printf("            Coordinates: %f, %f, %f\n", localPosition[0], localPosition[1], localPosition[2]);

                // ��ġ���� ��´�.
                _meshes.back().vertices[i * 3 + j].position = {static_cast<float>(localPosition[0]),
                                                               static_cast<float>(localPosition[1]),
                                                               static_cast<float>(localPosition[2])};

                // ���� ������ ���� ��´�
                _meshes.back().faces[i].indices[j] = vertexId; /*controlPointIndex;*/
            }

            /// --------------
            /// Vertex Color
            /// --------------

            // �÷����� ��� ������ �غ��Ѵ�.
            FbxColor vertexColor;

            int eColorCount = mesh->GetElementVertexColorCount();

            // �÷��� ������ ���� ǥ���Ѵ�.
            //if (eColorCount)
            //    _meshes.back()->_hasColor = true;

            for (l = 0; l < eColorCount; l++)
            {
                //_meshes.back()->_hasColor             = true;
                FbxGeometryElementVertexColor* leVtxc = mesh->GetElementVertexColor(l);
                FBXSDK_sprintf(header, 100, "            Color vertex: ");

                switch (leVtxc->GetMappingMode())
                {
                    default:
                        break;
                    case FbxGeometryElement::eByControlPoint:
                        switch (leVtxc->GetReferenceMode())
                        {
                            case FbxGeometryElement::eDirect:
                            {
                                vertexColor = leVtxc->GetDirectArray().GetAt(controlPointIndex);
                                FBXSDK_printf("%s %f, %f, %f, %f\n",
                                              header,
                                              vertexColor[0],
                                              vertexColor[1],
                                              vertexColor[2],
                                              vertexColor[3]);
                            }
                            break;
                            case FbxGeometryElement::eIndexToDirect:
                            {
                                int id      = leVtxc->GetIndexArray().GetAt(controlPointIndex);
                                vertexColor = leVtxc->GetDirectArray().GetAt(id);
                                FBXSDK_printf("%s %f, %f, %f, %f\n",
                                              header,
                                              vertexColor[0],
                                              vertexColor[1],
                                              vertexColor[2],
                                              vertexColor[3]);
                            }
                            break;
                            default:
                                break; // other reference modes not shown here!
                        }
                        break;

                    case FbxGeometryElement::eByPolygonVertex:
                    {
                        switch (leVtxc->GetReferenceMode())
                        {
                            case FbxGeometryElement::eDirect:
                            {
                                vertexColor = leVtxc->GetDirectArray().GetAt(vertexId);
                                FBXSDK_printf("%s %f, %f, %f, %f\n",
                                              header,
                                              vertexColor[0],
                                              vertexColor[1],
                                              vertexColor[2],
                                              vertexColor[3]);
                            }
                            break;
                            case FbxGeometryElement::eIndexToDirect:
                            {
                                int id      = leVtxc->GetIndexArray().GetAt(vertexId);
                                vertexColor = leVtxc->GetDirectArray().GetAt(id);
                                FBXSDK_printf("%s %f, %f, %f, %f\n",
                                              header,
                                              vertexColor[0],
                                              vertexColor[1],
                                              vertexColor[2],
                                              vertexColor[3]);
                            }
                            break;
                            default:
                                break; // other reference modes not shown here!
                        }
                    }
                    break;

                    case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
                    case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
                    case FbxGeometryElement::eNone:      // doesn't make much sense for UVs
                        break;
                }

                // �÷� ���� ��´�.
                _meshes.back().vertices[i * 3 + j].color = {static_cast<float>(vertexColor[0]),
                                                            static_cast<float>(vertexColor[1]),
                                                            static_cast<float>(vertexColor[2]),
                                                            static_cast<float>(vertexColor[3])};

            } // for eColorCount

            /// ----
            /// UV
            /// ----

            // UV �����͸� ��� ������ �غ��Ѵ�.
            FbxVector2 uv;

            for (l = 0; l < mesh->GetElementUVCount(); ++l)
            {
                FbxGeometryElementUV* leUV = mesh->GetElementUV(l);
                FBXSDK_sprintf(header, 100, "            Texture UV: ");

                switch (leUV->GetMappingMode())
                {
                    default:
                        break;
                    case FbxGeometryElement::eByControlPoint:
                        switch (leUV->GetReferenceMode())
                        {
                            case FbxGeometryElement::eDirect:
                            {
                                uv = leUV->GetDirectArray().GetAt(controlPointIndex);
                                FBXSDK_printf("%s %f, %f\n", header, uv[0], uv[1]);
                            }
                            break;
                            case FbxGeometryElement::eIndexToDirect:
                            {
                                int id = leUV->GetIndexArray().GetAt(controlPointIndex);
                                uv     = leUV->GetDirectArray().GetAt(id);
                                FBXSDK_printf("%s %f, %f\n",
                                              header,
                                              leUV->GetDirectArray().GetAt(id)[0],
                                              leUV->GetDirectArray().GetAt(id)[1]);
                            }
                            break;
                            default:
                                break; // other reference modes not shown here!
                        }
                        break;

                    case FbxGeometryElement::eByPolygonVertex:
                    {
                        int lTextureUVIndex = mesh->GetTextureUVIndex(i, j);
                        switch (leUV->GetReferenceMode())
                        {
                            case FbxGeometryElement::eDirect:
                            case FbxGeometryElement::eIndexToDirect:
                            {
                                uv = leUV->GetDirectArray().GetAt(lTextureUVIndex);
                                FBXSDK_printf("%s %f, %f\n", header, uv[0], uv[1]);
                            }
                            break;
                            default:
                                break; // other reference modes not shown here!
                        }
                    }
                    break;

                    case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
                    case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
                    case FbxGeometryElement::eNone:      // doesn't make much sense for UVs
                        break;
                }

                // uv ��ǥ���� ��´�.
                _meshes.back().vertices[i * 3 + j].uv = {static_cast<float>(uv[0]), static_cast<float>(uv[1])};

            } // for PolygonSize

            /// --------------
            /// Vertex Normal
            /// --------------

            // �븻 ���� ��� ������ �̸� �غ��Ѵ�.
            FbxVector4 normal;

            int normalCount = mesh->GetElementNormalCount();

            // �븻 ���� ���� ǥ���Ѵ�.
            if (normalCount)
                _meshes.back().hasNormal = true;

            for (l = 0; l < normalCount; ++l)
            {
                FbxGeometryElementNormal* eNormal = mesh->GetElementNormal(l);
                FBXSDK_sprintf(header, 100, "            Normal: ");

                if (eNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (eNormal->GetReferenceMode())
                    {
                        case FbxGeometryElement::eDirect:
                        {
                            normal = eNormal->GetDirectArray().GetAt(vertexId);
                            FBXSDK_printf("%s %f, %f, %f\n", header, normal[0], normal[1], normal[2]);
                            int a = 3;
                        }
                        break;
                        case FbxGeometryElement::eIndexToDirect:
                        {
                            int id = eNormal->GetIndexArray().GetAt(vertexId);
                            normal = eNormal->GetDirectArray().GetAt(id);
                            FBXSDK_printf("%s %f, %f, %f\n", header, normal[0], normal[1], normal[2]);
                        }
                        break;
                        default:
                            break; // other reference modes not shown here!
                    }

                    // �븻 ���� ��´�.
                    _meshes.back().vertices[i * 3 + j].normal = {static_cast<float>(normal[0]),
                                                                 static_cast<float>(normal[1]),
                                                                 static_cast<float>(normal[2])};

                } // for normalCount
            }

            /// ---------
            /// Tangent
            /// ---------

            // ź��Ʈ ���� ��� ������ �غ��Ѵ�.
            FbxVector4 tangent;

            int tangentCount = mesh->GetElementTangentCount();

            // ź��Ʈ ���� ������ ǥ���Ѵ�.
            if (tangentCount)
                _meshes.back().hasTangent = true;

            for (l = 0; l < tangentCount; ++l)
            {
                FbxGeometryElementTangent* eTangent = mesh->GetElementTangent(l);
                FBXSDK_sprintf(header, 100, "            Tangent: ");

                if (eTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (eTangent->GetReferenceMode())
                    {
                        case FbxGeometryElement::eDirect:
                        {
                            tangent = eTangent->GetDirectArray().GetAt(vertexId);
                            FBXSDK_printf("%s %f, %f, %f\n", header, tangent[0], tangent[1], tangent[2]);
                        }
                        break;
                        case FbxGeometryElement::eIndexToDirect:
                        {
                            int id  = eTangent->GetIndexArray().GetAt(vertexId);
                            tangent = eTangent->GetDirectArray().GetAt(id);
                            FBXSDK_printf("%s %f, %f, %f\n", header, tangent[0], tangent[1], tangent[2]);
                        }
                        break;
                        default:
                            break; // other reference modes not shown here!
                    }
                }

                // ź��Ʈ ���� ��´�.
                _meshes.back().vertices[i * 3 + j].tangent = {static_cast<float>(tangent[0]),
                                                              static_cast<float>(tangent[1]),
                                                              static_cast<float>(tangent[2])};

            } // for tangentCount

            /// ---------
            /// Binormal
            /// ---------

            // ���̳븻 ���� ��� ������ �غ��Ѵ�.

            FbxVector4 bitangent;

            for (l = 0; l < mesh->GetElementBinormalCount(); ++l)
            {
                FbxGeometryElementBinormal* eBinormal = mesh->GetElementBinormal(l);

                FBXSDK_sprintf(header, 100, "            Binormal: ");
                if (eBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (eBinormal->GetReferenceMode())
                    {
                        case FbxGeometryElement::eDirect:
                        {
                            bitangent = eBinormal->GetDirectArray().GetAt(vertexId);
                            FBXSDK_printf("%s %f, %f, %f\n", header, bitangent[0], bitangent[1], bitangent[2]);
                        }
                        break;
                        case FbxGeometryElement::eIndexToDirect:
                        {
                            int id    = eBinormal->GetIndexArray().GetAt(vertexId);
                            bitangent = eBinormal->GetDirectArray().GetAt(id);
                            FBXSDK_printf("%s %f, %f, %f\n", header, bitangent[0], bitangent[1], bitangent[2]);
                        }
                        break;
                        default:
                            break; // other reference modes not shown here!
                    }
                }

                // ���̳븻 ���� ��´�.
                _meshes.back().vertices[i * 3 + j].binormal = {static_cast<float>(bitangent[0]),
                                                               static_cast<float>(bitangent[1]),
                                                               static_cast<float>(bitangent[2])};

            } // for Binormal Count

            FBXSDK_printf("            >>> Vertex ID: %d\n\n", vertexId);

            vertexId++;
        } // for polygonSize
    }     // for polygonCount

    // check visibility for the edges of the mesh
    for (int l = 0; l < mesh->GetElementVisibilityCount(); ++l)
    {
        FbxGeometryElementVisibility* leVisibility = mesh->GetElementVisibility(l);
        FBXSDK_sprintf(header, 100, "    Edge Visibility : ");
        // DisplayString(header);
        switch (leVisibility->GetMappingMode())
        {
            default:
                break;
                // should be eByEdge
            case FbxGeometryElement::eByEdge:
                // should be eDirect
                for (j = 0; j != mesh->GetMeshEdgeCount(); ++j)
                {
                    FBXSDK_printf("        Edge %d\n", j);
                    FBXSDK_printf("              Edge visibility: %s\n",
                                  leVisibility->GetDirectArray().GetAt(j) ? "true" : "false");
                }

                break;
        }
    }
}