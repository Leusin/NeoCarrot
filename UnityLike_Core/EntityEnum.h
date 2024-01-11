/// EntityEnum.h: Ŭ���� ���ø� Entity �� �����ϴ� ������ Ŭ�������� �����Ͽ����ϴ�.
///
/// 2024-01-09

#pragma once

namespace core
{

enum class Tag
{
    CAMERA,

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
    BOX,

    GAMEOBJECT_COUNT
};

} // namespace game