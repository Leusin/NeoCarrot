/// Object.h : 게임 엔진에서 모든 객체의 기본 클래스 입니다.
/// 이를 통해 여러가지 공통된 기능을 사용할 수 있습니다.
///
/// Object 클래스의 주요 기능
///    - 식별자와 이름
///    - 또한 객체의 활성 여부
///    - 태깅과 레이어
///    - Destory 및 Instantiate
///
/// 2024-01-06


#pragma once

#include <memory>
#include <string>

namespace core
{

template <typename Tag, typename Layer>
class Object : public std::enable_shared_from_this<Object<Tag, Layer>>
{
    /// <summary>
    /// Object 클래스는 직접 생성하지 못하게 하도록
    /// protected 범위 지정자 에서 선언
    /// </summary>

protected:
    Object(int id, std::string name, Tag tag, Layer layer);

public:
    /// <summary>
    /// 상속을 위한 가상 소멸자.
    /// </summary>
    ~Object();

public:
    /// <summary>
    /// 객체를 소멸시키는데 사용됩니다.
    ///    사용처: 불필요한 객체 삭제, 씬 전환시 이전씬의 객체 정리
    /// </summary>
    virtual void Destroy();

    /// <summary>
    /// 프리팹(Prefab) 기반으로 새로운 게임 오브젝트를 생성합니다.
    ///
    /// TODO
    ///    해당 함수를 어떻게 구현해볼건지 좀 더 고민
    ///
    /// </summary>
    //virtual void Instantiate();

public:
    //constexpr int&         GetId() const;
    //constexpr std::string& GetName() const;

public:
    /// <summary>
    /// 객체의 활성 여부.
    /// </summary>
    bool _isActive{false};

    /// <summary>
    /// 오브젝트의 유사한 속성이나
    /// 역할을 식별하는데 사용하는 데이터.
    /// </summary>
    Tag   _tag;
    Layer _layer;

private:
    /// <summary>
    /// 객체를 식별 및 검색을 위한 데이터.
    /// </summary>
    const int         _id;
    const std::string _name;
};

} // namespace core

#include "Object.inl"