/// GetFbxMesh.h
///
/// 2024-01-23


#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"

#include <string>
namespace loader{class FbxLoader;}

namespace graphics
{

class GetFbxMesh: public core::IComponent, public core::GetEntity
{
public:
    GetFbxMesh(EntityPtr entityPtr, loader::FbxLoader* fbxLoader, std::string file);

    virtual void SetVertexBuffer(model::Mesh& data) abstract;
    void SetIndexBuffer(model::Mesh& data);
};

} // namespace graphics