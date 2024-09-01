

add_library(SRC INTERFACE)

#  添加定义
target_compile_definitions(SRC INTERFACE 

)

# 查找源文件
file(GLOB_RECURSE C_SOURCE CONFIGURE_DEPENDS 
    ./inc/*.h
    ./*.c
    ${PROJECT_SOURCE_DIR}/StartAndLink/STM32F4/*.s
)

# 链接头文件
target_include_directories(SRC INTERFACE 
    ./inc
)

# 链接源文件
target_sources(SRC
    INTERFACE 
    ${C_SOURCE}

)

# 链接相关第三方头文件
target_link_directories(SRC INTERFACE

)
# 链接相关第三方库文件
target_link_libraries(SRC INTERFACE

)

