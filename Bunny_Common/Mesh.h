#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace model
{

struct Vertex
{
    math::Vector3<float> position;
    math::Vector2<float> uv;
    math::Vector4<float> normal;
    math::Vector4<float> tangent;
    math::Vector4<float> binormal;
};

struct Face
{
    size_t indices[3];
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<Face>   faces;
};

} // namespace model