set(FFMPEG_PATH "F:/third/ffmpeg-master-latest-win64-gpl-shared" CACHE PATH "the ffmpeg path")

set(ffmpeg_avcodec_dll "${FFMPEG_PATH}/bin/avcodec-61.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avutil_dll "${FFMPEG_PATH}/bin/avutil-59.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avdevice_dll "${FFMPEG_PATH}/bin/avdevice-61.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avfilter_dll "${FFMPEG_PATH}/bin/avfilter-10.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avformat_dll "${FFMPEG_PATH}/bin/avformat-61.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_postproc_dll "${FFMPEG_PATH}/bin/postproc-58.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_swresample_dll "${FFMPEG_PATH}/bin/swresample-5.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_swscale_dll "${FFMPEG_PATH}/bin/swscale-8.dll" CACHE INTERNAL "theffmpeg_avcodec dll")

set(exec_prefix "${FFMPEG_PATH}")
set(bindir "${exec_prefix}/bin")
set(libdir "${exec_prefix}/lib")
set(includedir "${FFMPEG_PATH}/include")


macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

set_and_check(FFMPEG_PREFIX         "${FFMPEG_PATH}")
set_and_check(FFMPEG_EXEC_PREFIX    "${exec_prefix}")
set_and_check(FFMPEG_BINDIR         "${bindir}")
set_and_check(FFMPEG_INCLUDE_DIR    "${includedir}")
set_and_check(FFMPEG_LIBDIR         "${libdir}")


unset(FFMPEG_PATH)
unset(ffmpeg_avcodec_dll)
unset(ffmpeg_avutil_dll)
unset(ffmpeg_avdevice_dll)
unset(ffmpeg_avfilter_dll)
unset(ffmpeg_avformat_dll)
unset(ffmpeg_postproc_dll)
unset(ffmpeg_swresample_dll)
unset(ffmpeg_swscale_dll)
unset(exec_prefix)
unset(bindir)
unset(libdir)
unset(includedir)

add_library(ffmpeg_avcodec SHARED IMPORTED GLOBAL)
list(APPEND _ffmpeg_avcodec_libdirs "${FFMPEG_LIBDIR}")
target_include_directories(ffmpeg_avcodec INTERFACE "${FFMPEG_PATH}/include")
set_target_properties(ffmpeg_avcodec
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avcodec-61.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/libavcodec.dll.a"   
    IMPORTED_LINK_INTERFACE_LANGUAGES "C" 
    INTERFACE_LINK_DIRECTORIES "${_ffmpeg_avcodec_libdirs}"
    INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIR}"
)

add_library(ffmpeg_avutil SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_avutil
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avutil-59.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/libavutil.dll.a"    
)

add_library(ffmpeg_avdevice SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_avdevice
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avdevice-61.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/libavdevice.dll.a"    
)

add_library(ffmpeg_avfilter SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_avfilter
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avfilter-10.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/libavfilter.dll.a"    
)

add_library(ffmpeg_avformat SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_avformat
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avformat-61.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/libavformat.dll.a"    
)

add_library(ffmpeg_postproc SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_postproc
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/postproc-58.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/libpostproc.dll.a"    
)

add_library(ffmpeg_swresample SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_swresample
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/swresample-5.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/libswresample.dll.a"    
)

add_library(ffmpeg_swscale SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_swscale
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/swscale-8.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/libswscale.dll.a"    
)

