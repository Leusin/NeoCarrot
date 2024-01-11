/// GraphicsInfo.h : 그래픽스에게 전달할 데이터 정의한 그래픽스 입니다.
///
/// 2023-01-11

#pragma once

//#include "WindowInfo.h"
#include "CameraInfo.h"

namespace data
{

struct ForGraphics
{
    //WindowInfo* _win;
    CameraInfo _camera;
};

}
