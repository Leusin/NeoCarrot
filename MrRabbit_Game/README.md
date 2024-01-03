# MrRabbit_Game

## 프로젝트 설정 확인 할 것
1. [ 일반 > 출력 디렉터리 ] `$(SolutionDir)$(Platform)\$(Configuration)\`
1. [ C/C++ > 일반 > 추가 포함 디렉터리 ] `..\NeoCarrot_Graphics`
3. [ 라이브러리 관리자 > 일반 > 추가 종속성 ] `NeoCarrot_Graphics.lib`
4. [ 라이브러리 관리자 > 일반 > 추가 라이브러리 디렉터리 ] `$(SolutionDir)$(Platform)\$(Configuration)\`

## 종속성
- `<windows.h>`
- `"GraphicsEngine.h"`