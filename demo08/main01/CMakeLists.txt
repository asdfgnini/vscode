aux_source_directory(. SRC_FILE)
message("SRC_FILE: ${SRC_FILE}")

add_executable(app ${SRC_FILE})

target_compile_features(app PUBLIC cxx_std_17)
target_link_libraries(app PRIVATE OpenCV)

add_custom_command(TARGET app
    POST_BUILD  
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${opencv_dll} $<TARGET_FILE_DIR:app>)


    