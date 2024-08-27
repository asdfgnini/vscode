cmake_minimum_required(VERSION 3.20)

project(
    demo05
    LANGUAGES C CXX ASM
    VERSION 0.0.1
)

MESSAGE(STATUS "**** Building project: ${CMAKE_PROJECT_NAME}, Version: ${CMAKE_PROJECT_VERSION} ****")

# 彩色日志输出；
SET(CMAKE_COLOR_DIAGNOSTICS True)

# 生成 compile_commands.json，可配合 clangd 实现精准的代码关联与跳转；
SET(CMAKE_EXPORT_COMPILE_COMMANDS True)

include("Toolchain/gcc-arm-none-eabi.cmake")  # 引入GCC ARM交叉编译工具链文件

# 创建可执行对象类型
add_executable(${CMAKE_PROJECT_NAME})  # 定义一个可执行文件目标

# 添加STM32CubeMX生成的源文件
add_subdirectory(Drivers)  
add_subdirectory(BSP/stm32) 
add_subdirectory(Src)  

# 添加链接库
target_link_libraries(${CMAKE_PROJECT_NAME}
    Driver
    BSP
    SRC
    # 添加用户定义的库
)