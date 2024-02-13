# NeoCarrot_Graphics

## 프로젝트 설정 확인 할 것
1. [ C++/C > 일반 ] `$(SolutionDir)\DirectXTK\Inc`
2. [ 일반 > 출력 디렉터리 ] `$(SolutionDir)$(Platform)\$(Configuration)\`
3. [ 라이브러리 관리자 > 일반 > 추가 종속성 ] `dxgi.lib`, `d3d11.lib`, `DirectXTK.lib`
4. [ 라이브러리 관리자 > 일반 > 추가 라이브러리 디렉터리 ] `$(SolutionDir)\DirectXTK\Lib\$(Platform)\$(Configuration)`

## 종속성
- DirectX : `<d3d11.h>`, `<DirectXColors.h>`, 
- DirectXTK: `<SpriteFont.h>`, `<SpriteBatch.h>`
- 디버깅용 : `<cassert>`
- ComPtr : `<wrl.h>`