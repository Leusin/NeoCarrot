#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <vector>

namespace model
{

struct Vertex
{
    math::Vector3<float> position;
    math::Vector2<float> uv;
    math::Vector3<float> normal;
    math::Vector3<float> tangent;
    math::Vector3<float> binormal;
    math::Vector4<float> color;
};

struct Face
{
    size_t indices[3];
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<Face>   faces;

    bool hasTexture{false};
    bool hasNormal{false};
    bool hasTangent{false};
    bool hasColor{false};
};

} // namespace model