/// EntityEnum.h: Ŭ���� ���ø� Entity �� �����ϴ� ������ Ŭ�������� �����Ͽ����ϴ�.
///
/// 2024-01-09

#pragma once

namespace core
{

enum class Tag
{
    CAMERA,
    MESHOBJ,
    GIZMO,

    TAG_COUNT
};
enum class Layer
{
    DEBUGINFO,
    FORGROUND,
    BACKGROUND,

    LAYERCOUNT
};

enum class GameObect
{
    CAMERA,
    GRID,
    AXIS,
    BOX,
    BOX2,

    GAMEOBJECT_COUNT
};

} // namespace game