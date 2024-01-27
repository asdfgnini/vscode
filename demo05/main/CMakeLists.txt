
aux_source_directory(./src SRC_FILE)

add_executable(${PROJECT_NAME} main.cpp ${SRC_FILE})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_directories(${PROJECT_NAME} PUBLIC 
    SDL
    ffmpeg_avcodec
    ffmpeg_avutil

)



