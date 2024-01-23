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
    //BOX,
    //TRIANGLE,
    //RAINBOWBOX,
    TUTORIAL04,
    TUTORIAL05,
    //LIGHTBOX1,
    TUTIRIAL06,

    GAMEOBJECT_COUNT
};

} // namespace core