cmake_minimum_required(VERSION 3.21)

project(
    MEDIA
    LANGUAGES CXX C
    DESCRIPTION "my cmake"
    VERSION 0.1.0
)

set(media_name learnSDL)

add_subdirectory(Main)
add_subdirectory(3rdlibs)