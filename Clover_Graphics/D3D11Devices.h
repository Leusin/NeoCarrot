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
    /// DirectX ���ҽ� ��ü�� �����ϴ� �׷��Ƚ� COM �������̽�.
    /// </summary>
    Microsoft::WRL::ComPtr<ID3D11Device>        _d3dDevice;

    /// <summary>
    /// �������� ���� �׷��Ƚ� COM �������̽�
    /// CPU�� ������ �޸𸮿� �ִ� �׷��� ������ ���ҽ��� �����´�.
    /// </summary>
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dImmdiateContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dDeferredContext;
};

} // namespace graphics

//
// ID3D11Device
//    ���ҽ� ������ ���÷��� ��͸� ����� �����ϴµ� �����.
//
// ID3D11DeviceContext
//    ����̽��� ���� ȯ�� ������ ���������� ����, ����̽� ���ҽ��� 
//    ������ ����� ������ ������ �Ѵ�. 
// 
//    ����̽� ���ٽ�Ʈ�� ������, ���۵� ������ �� ������ �ִ�
// 
//    - Immdiate Context : ����̹��� ���� �������Ѵ�.
// 
//    - Deferred Context : GPU ����� ��� ������� �����Ѵ�. 
//    ��Ƽ ���������� ���Ǹ�, �̱� ������ ȯ�濡�� ����� �� ����
//
// 2024-01-15