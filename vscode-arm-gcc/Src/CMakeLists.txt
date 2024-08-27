cmake_minimum_required(VERSION 3.22)

add_library(SRC INTERFACE)

target_include_directories(SRC INTERFACE
    ./inc
)

target_sources(SRC INTERFACE
    ./main.c
    ../startup_stm32f429xx.s
)

target_link_directories(SRC INTERFACE
)

target_link_libraries(SRC INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
