# 프로젝트 설명
- 프로젝트명 : NeoCarrot 
- 프로젝트 기간 : 2023-12-22 ~
- 목표 : 게임 그래픽스 엔진 제작 및 그래픽스 학습.

---
# 프로젝트 속성 설정

## 공통
1. [ 일반 > 출력 디렉터리 ] `$(SolutionDir)$(Platform)\$(Configuration)\`

## CarrotClient_Demo
1. [ C++/C > 일반 ] `$(SolutionDir)\MrRabbit_Game`
2. [ 링커 > 일반 > 추가 라이브러리 디렉터리 ] `$(SolutionDir)$(Platform)\$(Configuration)\`
3. [ 링커 > 입력 > 추가 종속성 ] `MrRabbit_Game.lib`

## MrRabbit_Game
1. [ C/C++ > 일반 > 추가 포함 디렉터리 ] `$(SolutionDir)\NeoCarrot_Graphics`
2. [ 라이브러리 관리자 > 일반 > 추가 종속성 ] `NeoCarrot_Graphics.lib`
	, `UnityLike_Core.lib`
	, `Bunny_Common.lib;`
3. [ 라이브러리 관리자 > 일반 > 추가 라이브러리 디렉터리 ] `$(SolutionDir)$(Platform)\$(Configuration)\`

## NeoCarrot_Graphics
1. [ C++/C > 일반 ] `$(SolutionDir)\DirectXTK\Inc`
2. [ 라이브러리 관리자 > 일반 > 추가 종속성 ] `Penguin_FBXLoader.lib`
	, `DirectXTK.lib`
	, `d3d11.lib`
	, `Effects11d.lib`
	, `d3dcompiler.lib`
3. [ 라이브러리 관리자 > 일반 > 추가 라이브러리 디렉터리 ] `$(SolutionDir)$(Platform)\$(Configuration)`
	, `$(SolutionDir)DirectXTK\Lib\$(Platform)\$(Configuration)`
	, `$(SolutionDir)FX11\Lib\$(Platform)\$(Configuration)`