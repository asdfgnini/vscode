
# 设置C++编译器的参数设定
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mconsole")  # 设定以控制台方式编译还是以窗口模式编译


# 添加可执行文件
add_executable(demo03 main.cpp)

# 链接第三方库
target_link_libraries(demo03 PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image
    ffmpeg_avformat
    ffmpeg_avcodec  
    Qt6::Core
    Qt6::Widgets
)



#设定宏函数，用以搬运dll
macro(ADDTest target_name)
    add_custom_command(TARGET demo03
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${${target_name}} $<TARGET_FILE_DIR:demo03>)
endmacro(ADDTest target_name)

ADDTest(ffmpeg_avcodec_dll)
ADDTest(ffmpeg_avutil_dll)
ADDTest(ffmpeg_avdevice_dll)
ADDTest(ffmpeg_avfilter_dll)
ADDTest(ffmpeg_avformat_dll)
ADDTest(ffmpeg_postproc_dll)
ADDTest(ffmpeg_swresample_dll)
ADDTest(ffmpeg_swscale_dll)
ADDTest(__SDL2_dll)
ADDTest(__SDL2_IMAGE_dll)
