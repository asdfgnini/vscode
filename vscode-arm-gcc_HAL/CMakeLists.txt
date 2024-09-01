cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_EXPORT_COMPILE_COMMANDS True)


project(
    gcc_hal
    LANGUAGES C CXX ASM
    VERSION 0.0.1
)

MESSAGE(STATUS "**** Building project: ${CMAKE_PROJECT_NAME}, Version: ${CMAKE_PROJECT_VERSION} ****")

if (PROJECT_BINARY_DIR STREQUAL PROJET_SOURCE_DIR)
	message(WARNING "The binary directory of CMake cannot be the same as source directory!")
endif()

include("Toolchain/STM32F4/gcc-arm-none-eabi.cmake")  # 引入GCC ARM交叉编译工具链文件


add_executable(${CMAKE_PROJECT_NAME})  # 定义一个可执行文件目标

add_subdirectory(Drivers/STM32F4)
add_subdirectory(Src/STM32F4)
add_subdirectory(BSP/STM32F4)

target_link_libraries(${CMAKE_PROJECT_NAME}
    STM32F4_BSP   
    STM32F4_Driver
    SRC
)

