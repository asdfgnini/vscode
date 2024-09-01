
# 添加目标
add_library(STM32F4_Driver INTERFACE)

#  设置宏定义
target_compile_definitions(STM32F4_Driver INTERFACE
    USE_HAL_DRIVER 
    STM32F429xx
)

# 查找源文件
file(GLOB_RECURSE C_SOURCE CONFIGURE_DEPENDS 
    ./STM32F4xx_HAL_Driver/Src/*.c 
    ./STM32F4xx_HAL_Driver/Inc/*.h 
    ./CMSIS/Device/ST/STM32F4xx/Include/*.h
    ./CMSIS/Include/*.h
)

# 链接头文件
target_include_directories(STM32F4_Driver INTERFACE 
    ./STM32F4xx_HAL_Driver/Inc
    ./CMSIS/Device/ST/STM32F4xx/Include
    ./CMSIS/Include
)

target_sources(
    STM32F4_Driver
    INTERFACE 
    ${C_SOURCE}
)