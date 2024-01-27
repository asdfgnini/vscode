
set(FFMPEG_PATH "G:/ffmpeg-6.1.1-full_build-shared" CACHE PATH "the ffmpeg path")

find_library(LIB_VAR avcodec.lib PATHS G:/ffmpeg-6.1.1-full_build-shared/lib)
message(${LIB_VAR})

set(ffmpeg_avcodec_dll "${FFMPEG_PATH}/bin/avcodec-60.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avutil_dll "${FFMPEG_PATH}/bin/avutil-58.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avdevice_dll "${FFMPEG_PATH}/bin/avdevice-60.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avfilter_dll "${FFMPEG_PATH}/bin/avfilter-9.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_avformat_dll "${FFMPEG_PATH}/bin/avformat-60.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_postproc_dll "${FFMPEG_PATH}/bin/postproc-57.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_swresample_dll "${FFMPEG_PATH}/bin/swresample-4.dll" CACHE INTERNAL "theffmpeg_avcodec dll")
set(ffmpeg_swscale_dll "${FFMPEG_PATH}/bin/swscale-7.dll" CACHE INTERNAL "theffmpeg_avcodec dll")


add_library(ffmpeg_avcodec SHARED IMPORTED GLOBAL)
target_include_directories(ffmpeg_avcodec INTERFACE "${FFMPEG_PATH}/include")
set_target_properties(ffmpeg_avcodec
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avcodec-60.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avcodec.lib"    
)

add_library(ffmpeg_avutil SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_avutil
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avutil-58.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avutil.lib"    
)

add_library(ffmpeg_avdevice SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_avdevice
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avdevice-60.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avdevice.lib"    
)

add_library(ffmpeg_avfilter SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_avfilter
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avfilter-9.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avfilter.lib"    
)

add_library(ffmpeg_avformat SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_avformat
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avformat-60.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avformat.lib"    
)

add_library(ffmpeg_postproc SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_postproc
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/postproc-57.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/postproc.lib"    
)

add_library(ffmpeg_swresample SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_swresample
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/swresample-4.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/swresample.lib"    
)

add_library(ffmpeg_swscale SHARED IMPORTED GLOBAL)
set_target_properties(ffmpeg_swscale
    PROPERTIES
    IMPORTED_LOCATION "${FFMPEG_PATH}/bin/swscale-7.dll"
    IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/swscale.lib"    
)


# set_target_properties(ffmpeg 
#     PROPERTIES 
#     IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avcodec-60.dll"
#     IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avdevice-60.dll"
#     IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avfilter-9.dll"
#     IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avformat-60.dll"
#     IMPORTED_LOCATION "${FFMPEG_PATH}/bin/avutil-58.dll"
#     IMPORTED_LOCATION "${FFMPEG_PATH}/bin/postproc-57.dll"
#     IMPORTED_LOCATION "${FFMPEG_PATH}/bin/swresample-4.dll"
#     IMPORTED_LOCATION "${FFMPEG_PATH}/bin/swscale-7.dll"
#     IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avcodec.lib"    
#     IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avdevice.lib"
#     IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avfilter.lib"
#     IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avformat.lib"
#     IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/avutil.lib"
#     IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/postproc.lib"
#     IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/swresample.lib"
#     IMPORTED_IMPLIB "${FFMPEG_PATH}/lib/swscale.lib"
#     ) 
