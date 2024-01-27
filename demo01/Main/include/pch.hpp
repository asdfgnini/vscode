#pragma once

#include <iostream>
using namespace std;

#include "opencv2/opencv.hpp"

#include "SDL.h"
/*
在SDL中定义了#define main SDL_main ，所以找不到main函数，下面代码取消SDL对main函数的定义，就正常了
但在visual stduio中不用进行下面的操作就可以运行
*/
#undef main 

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/pixfmt.h>
    #include <libavutil/time.h>
    #include <libswresample/swresample.h>
}

#include "threadpool.h"