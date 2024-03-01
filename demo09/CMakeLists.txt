cmake_minimum_required(VERSION 3.21)

project(demo09)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory(main05)

