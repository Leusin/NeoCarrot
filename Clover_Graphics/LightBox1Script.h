/// LightBox1Script.h
/// 2024-01-23

#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"

namespace graphics
{
class Transpose_mk2;

// º»¹®
class LightBox1Script: public core::IComponent, virtual core::GetEntity
{
public:
    LightBox1Script(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    void InitializeBuffers();
    void SetVertexBuffer(model::Mesh& data);
    void SetIndexBuffer(model::Mesh& data);

    void UpdateTick(float dt);
    void UpdateAnimation();
    void UpdateRender();

private:
    Transpose_mk2* _transpose;
    float _t1{ 0.0f };
    float _t2{ 0.0f };
};

} // namespace graphics