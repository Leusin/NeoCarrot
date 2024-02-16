/// 2024-01-15

#pragma once

#include <wrl.h>
#include <d3d11.h>

namespace graphics
{
class Devices
{
public:
    Devices();
    ~Devices();

    ID3D11Device*        Device() const;
    ID3D11DeviceContext* ImmediateContext() const;
    ID3D11DeviceContext* DeferredContext() const;

private:
    void CreateDeviceAndImmdiateContext();
    void CreateDeferredContext();

    /// <summary>
    /// DirectX 리소스 객체를 생성하는 그래픽스 COM 인터페이스.
    /// </summary>
    Microsoft::WRL::ComPtr<ID3D11Device>        _d3dDevice;

    /// <summary>
    /// 랜더링를 위한 그래픽스 COM 인터페이스
    /// CPU에 고정된 메모리에 있는 그래픽 데이터 리소스를 가져온다.
    /// </summary>
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dImmdiateContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dDeferredContext;
};

} // namespace graphics

//
// ID3D11Device
//    리소스 생성과 디스플레이 어뎁터를 기능을 나열하는데 사용함.
//
// ID3D11DeviceContext
//    디바이스에 대한 환경 설정과 파이프라인 설정, 디바이스 리소스로 
//    렌더링 명령을 내리는 역할을 한다. 
// 
//    디바이스 컨텐스트는 랜더링, 디퍼드 랜더링 두 종류가 있다
// 
//    - Immdiate Context : 드라이버에 직접 랜더링한다.
// 
//    - Deferred Context : GPU 명령을 명령 목록으로 저장한다. 
//    멀티 스레딩에서 사용되며, 싱글 스래드 환경에선 사용할 수 없다
//
// 2024-01-15