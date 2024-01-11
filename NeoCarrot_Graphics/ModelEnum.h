/// EntityEnum.h: Ŭ���� ���ø� Entity �� �����ϴ� ������ Ŭ�������� �����Ͽ����ϴ�.
///
/// 2024-01-09

#pragma once

namespace grahics
{

enum class Tag
{
    GIZMO,
    MESH,

    TAG_COUNT
};
enum class Layer
{
    DEBUGINFO,
    FORGROUND,
    BACKGROUND,

    LAYERCOUNT
};

enum class Model
{
    BOX,

    MODEL_COUNT
};

} // namespace game