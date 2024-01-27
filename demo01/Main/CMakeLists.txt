
#获取所有源文件
aux_source_directory(./src SDL_src)
foreach(var ${SDL_src})
    message(${var})
endforeach()

#获取头文件
# file(GLOB SDL_header_files ./include/*.h)

#递归获取头文件
file(GLOB_RECURSE SDL_header_files_h ./include/*.h)
file(GLOB_RECURSE SDL_header_files_hpp ./include/*.hpp)

foreach(var ${SDL_header_files_h})
    message(${var})
endforeach()

foreach(var ${SDL_header_files_hpp})
message(${var})
endforeach()

# 是否需要将所有源文件和头文件放到这里，取决于你生成的工程是否需要这个文件，如果需要那就加上
add_executable(${sdl_name} ${SDL_src} ${SDL_header_files_h} ${SDL_header_files_hpp})
target_include_directories(${sdl_name} PUBLIC include)
target_compile_features(${sdl_name} PUBLIC cxx_std_17)
target_link_libraries(${sdl_name} PUBLIC 
    OpenCV 
    SDL 
    ffmpeg_avcodec 
    ffmpeg_avutil 
    ffmpeg_avformat 
    ffmpeg_avdevice 
    ffmpeg_avfilter 
    ffmpeg_postproc 
    ffmpeg_swresample 
    ffmpeg_swscale
    threadpool
    )

# target_precompile_headers(${sdl_name} PUBLIC ./include/pch.hpp)




# #添加自定义命令 拷贝动态库
# macro(COPY_DLL target_name dll_path)
#     add_custom_command(TARGET ${target_name} POST_BUILD  
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${dll_path} $<TARGET_FILE_DIR:${target_name}>)
# endmacro(COPY_DLL)

# COPY_DLL(${sdl_name} opencv_dll)

# add_custom_command(TARGET ${sdl_name}
#     POST_BUILD  
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${opencv_dll} $<TARGET_FILE_DIR:${sdl_name}>)

# #添加自定义命令 拷贝动态库
# add_custom_command(TARGET ${sdl_name}
#     POST_BUILD  
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${sdl_dll} $<TARGET_FILE_DIR:${sdl_name}>)

