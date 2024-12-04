# 设置FFmpeg路径
set(FFMPEG_PATH "C:/foloheart/3rdlibs/ffmpeg" CACHE PATH "The FFmpeg path")
set(exec_prefix "${FFMPEG_PATH}")
set(bindir "${exec_prefix}/bin")
set(libdir "${exec_prefix}/lib")
set(includedir "${FFMPEG_PATH}/include")

# 暴露给外界，搬运DLL
set(ffmpeg_avcodec_dll "${FFMPEG_PATH}/bin/avcodec-61.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avutil_dll "${FFMPEG_PATH}/bin/avutil-59.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avdevice_dll "${FFMPEG_PATH}/bin/avdevice-61.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avfilter_dll "${FFMPEG_PATH}/bin/avfilter-10.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avformat_dll "${FFMPEG_PATH}/bin/avformat-61.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_postproc_dll "${FFMPEG_PATH}/bin/postproc-58.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_swresample_dll "${FFMPEG_PATH}/bin/swresample-5.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_swscale_dll "${FFMPEG_PATH}/bin/swscale-8.dll" CACHE INTERNAL "theffmpeg_avcodec dll")

# 定义需要导入的 FFmpeg 库名称
set(ffmpeg_libraries
    avcodec-61.dll
    avutil-59.dll
    avdevice-61.dll
    avfilter-10.dll
    avformat-61.dll
    postproc-58.dll
    swresample-5.dll
    swscale-8.dll
)

# 检查路径的有效性
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist!")
    endif()
endmacro()

set_and_check(FFMPEG_PREFIX "${FFMPEG_PATH}")
set_and_check(FFMPEG_EXEC_PREFIX "${exec_prefix}")
set_and_check(FFMPEG_BINDIR "${bindir}")
set_and_check(FFMPEG_INCLUDE_DIR "${includedir}")
set_and_check(FFMPEG_LIBDIR "${libdir}")

# 为每个 DLL 创建库，并设置目标属性
foreach(lib ${ffmpeg_libraries})
    # 提取不带版本号的库名称
    string(REPLACE ".dll" "" lib_name ${lib})
    string(REGEX REPLACE "[-0-9]+$" "" lib_name_no_version ${lib_name})  # 去掉版本号部分

    # 创建共享库，标记为 IMPORTED，表示这些库是外部依赖
    add_library(ffmpeg_${lib_name_no_version} SHARED IMPORTED GLOBAL)
    # message("lib_name_no_version: ${lib_name_no_version}")

    # target_include_directories(ffmpeg_${lib_name_no_version} INTERFACE "${FFMPEG_PATH}/include")
    
    # 设置目标属性，指定库的位置、实现库和包含路径
    set_target_properties(ffmpeg_${lib_name_no_version}
        PROPERTIES
        IMPORTED_LOCATION "${FFMPEG_PATH}/bin/${lib}"  # DLL文件的位置
        IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/lib${lib_name_no_version}.dll.a"  # 导入库文件（没有版本号）
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"  # 链接语言
        INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIR}"  # 设置包含头文件的目录
        INTERFACE_LINK_DIRECTORIES "${FFMPEG_LIBDIR}"  # 设置库文件的目录
    )
endforeach()

# 清理不再需要的变量
unset(FFMPEG_PATH)
unset(ffmpeg_libraries)
unset(exec_prefix)
unset(bindir)
unset(libdir)
unset(includedir)

