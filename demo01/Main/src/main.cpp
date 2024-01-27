#include "pch.hpp"

extern "C"{
    
    #include "clac.h"
}

void fun1(int slp)
{
	std::cout << " hello, fun1 ! " << std::this_thread::get_id() << std::endl;
	// printf("  hello, fun1 !  %d\n" ,std::this_thread::get_id());
	if (slp > 0)
	{
		std::cout << " ======= fun1 sleep " << slp << "  ========= " << std::this_thread::get_id() << std::endl;
		// printf(" ======= fun1 sleep %d  =========  %d\n",slp, std::this_thread::get_id());
		std::this_thread::sleep_for(std::chrono::milliseconds(slp));
		//Sleep(slp );
	}
}


AVFormatContext* m_pAVformatContext = nullptr;
string FilePath = "C:/Users/22231/Desktop/vscode/demo01/res/dove_640x360.mp4";

int main(int argc,char*argv[])
{
    cout << "[SDL:] ";
    SDL_Log("hello SDL");

    cout << "[opencv:] " << CV_VERSION << endl;

    cout << "[ffmpeg:] " << av_version_info() << endl;

    cout << "[custercom:] ";
    add(1,2);

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

    try
    {
      std::threadpool executor{ 50 };
      std::future<void> ff = executor.commit(fun1,0);

      std::cout << std::endl << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(3));
      
      ff.get(); //调用.get()获取返回值会等待线程执行完,获取返回值
    }
    catch(const std::exception& e)
    {
      std::cout << "some unhappy happened...  " << std::this_thread::get_id() << e.what() << std::endl;
    }
  

    return 0;

}