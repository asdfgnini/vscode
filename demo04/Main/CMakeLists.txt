

add_executable(media src/main.cpp)
# target_link_libraries(media ffmpeg)
target_compile_features(media PUBLIC cxx_std_17)

target_link_libraries(media PUBLIC 
        ffmpeg_avcodec 
        ffmpeg_avutil 
        ffmpeg_avformat 
        ffmpeg_avdevice 
        ffmpeg_avfilter 
        ffmpeg_postproc 
        ffmpeg_swresample 
        ffmpeg_swscale)

