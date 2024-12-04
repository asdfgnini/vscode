cmake_minimum_required(VERSION 3.21)

project(demo03)

## QT
# 对于Qt所提供的cmake脚本，所定义的目标是局部的，只能往find_package本目录和子目录传递目标，不能向父目录传递目标
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt/6.7.3/llvm-mingw_64/lib/cmake")


# 查找 Qt6 模块，确保 Core 和 Widgets 被找到
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
# 检查 Qt6 是否成功找到，并输出相应的提示信息

if(Qt6_FOUND)
    message(STATUS "Qt6 Core and Widgets found successfully.")
else()
    message(FATAL_ERROR "Qt6 Core and/or Widgets not found!")
endif()

# 配置 Qt 项目环境，使用 Qt 标准项目设置
qt_standard_project_setup()

# 输出 qt_standard_project_setup 执行后的状态信息
message(STATUS "Qt standard project setup complete.")




# 自定义的cmake导入脚本，有些是库作者提供，有些是自己写的，所定义的目标都是全局目标，可以向父目录进行传递
add_subdirectory(3rdlibs)

# 主程序
add_subdirectory(src)

message("CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
