/// EntityEnum.h: 클레스 템플릿 Entity 를 구성하는 열거형 클래스들을 정의하였습니다.
///
/// 2024-01-09

#pragma once

namespace game
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

enum class Entity
{
    CAMERA,

    ENTITY_COUNT
};

} // namespace game