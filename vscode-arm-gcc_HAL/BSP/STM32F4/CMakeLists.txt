
add_library(STM32F4_BSP INTERFACE)

target_compile_definitions(STM32F4_BSP INTERFACE 

)

file(GLOB_RECURSE C_SOURCE 
    ./*.c 
    ./*.h 
    ./src/*.c 
    ./inc/*.h
)

target_include_directories(STM32F4_BSP INTERFACE 
    ./
    ./inc
)

target_sources(STM32F4_BSP INTERFACE 
    ${C_SOURCE}
)