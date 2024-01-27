cmake_minimum_required(VERSION 3.21)


# 这里可以指定本次工程的语言 描述 和 本次工程的版本
project(
    MEDIA
    LANGUAGES CXX C
    DESCRIPTION "my cmake"
    VERSION 0.1.0
)

#输出compile_commands.json文件，供给其他使用，例如vscode的c_cpp_properties.json在文件中指定compileCommands的路径为compile_commands.json文件
set(EXPORT_COMPILE_COMMANDS ON)

set(sdl_name media)

add_subdirectory(3rdlibs)
add_subdirectory(Main)
