#include "SDL.h"

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
#include <iostream>
using namespace std;

int main(int argc,char*argv[])
{   
    SDL_Log("hello world");

    cout << "[ffmpeg:] " << av_version_info() << endl;
    
    
    return 0;
}