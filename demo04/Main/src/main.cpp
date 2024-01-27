
#include <iostream>
using namespace std;

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
AVFormatContext* m_pAVformatContext = nullptr;
string FilePath = "C:\\Users\\22231\\Desktop\\ffmpeg\\demo01\\dove_640x360.mp4";
int main()
{

    printf("%s\r\n",av_version_info());
    cout << av_version_info() << endl;

    bool re_value = avformat_open_input(&m_pAVformatContext, FilePath.c_str(), NULL, NULL);
    if(re_value)
    { 
      char err_buffer[1024] = { 0 };
      av_strerror(re_value, err_buffer, sizeof(err_buffer));
      cout << "Demux: " << "open " << FilePath << "fail: " << err_buffer;

    }
    else
    {
      cout << "OK" << endl;
    }
    return 0;
} 