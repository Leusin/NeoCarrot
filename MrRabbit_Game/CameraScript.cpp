#include "CameraScript.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

CameraScript::CameraScript()
{
}

CameraScript::~CameraScript()
{
}

void CameraScript::Update(float dt)
{
#ifdef _DEBUG
    std::cout << "\tCameraScript Update!!!\n";
#endif // _DEBUG
}

}