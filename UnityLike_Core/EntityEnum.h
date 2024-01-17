/// EntityEnum.h: 클레스 템플릿 Entity 를 구성하는 열거형 클래스들을 정의하였습니다.
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