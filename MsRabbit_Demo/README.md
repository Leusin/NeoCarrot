# ������Ʈ ����
- ������Ʈ�� : NeoCarrot 
- ������Ʈ �Ⱓ : 2023-12-22 ~
- ��ǥ : ���� �׷��Ƚ� ���� ���� �� �׷��Ƚ� �н�.

---
# ������Ʈ �Ӽ� ����

## ����
1. [ �Ϲ� > ��� ���͸� ] `$(SolutionDir)$(Platform)\$(Configuration)\`

## CarrotClient_Demo
1. [ C++/C > �Ϲ� ] `$(SolutionDir)\MrRabbit_Game`
2. [ ��Ŀ > �Ϲ� > �߰� ���̺귯�� ���͸� ] `$(SolutionDir)$(Platform)\$(Configuration)\`
3. [ ��Ŀ > �Է� > �߰� ���Ӽ� ] `MrRabbit_Game.lib`

## MrRabbit_Game
1. [ C/C++ > �Ϲ� > �߰� ���� ���͸� ] `$(SolutionDir)\NeoCarrot_Graphics`
2. [ ���̺귯�� ������ > �Ϲ� > �߰� ���Ӽ� ] `NeoCarrot_Graphics.lib`
	, `UnityLike_Core.lib`
	, `Bunny_Common.lib;`
3. [ ���̺귯�� ������ > �Ϲ� > �߰� ���̺귯�� ���͸� ] `$(SolutionDir)$(Platform)\$(Configuration)\`

## NeoCarrot_Graphics
1. [ C++/C > �Ϲ� ] `$(SolutionDir)\DirectXTK\Inc`
2. [ ���̺귯�� ������ > �Ϲ� > �߰� ���Ӽ� ] `Penguin_FBXLoader.lib`
	, `DirectXTK.lib`
	, `d3d11.lib`
	, `Effects11d.lib`
	, `d3dcompiler.lib`
3. [ ���̺귯�� ������ > �Ϲ� > �߰� ���̺귯�� ���͸� ] `$(SolutionDir)$(Platform)\$(Configuration)`
	, `$(SolutionDir)DirectXTK\Lib\$(Platform)\$(Configuration)`
	, `$(SolutionDir)FX11\Lib\$(Platform)\$(Configuration)`