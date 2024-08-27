
cmake_minimum_required(VERSION 3.22)


add_library(BSP INTERFACE)

target_compile_definitions(BSP INTERFACE 

)

target_include_directories(BSP INTERFACE
    ./
    ./inc

)


target_sources(
  BSP
  INTERFACE # {{BEGIN_TARGET_SOURCES}}
  ${CMAKE_CURRENT_LIST_DIR}/bsp.c
  ${CMAKE_CURRENT_LIST_DIR}/stm32f4xx_it.c
  ${CMAKE_CURRENT_LIST_DIR}/system_stm32f4xx.c
    ${CMAKE_CURRENT_LIST_DIR}/src/bsp_ext_io.c
    ${CMAKE_CURRENT_LIST_DIR}/src/bsp_led.c
    ${CMAKE_CURRENT_LIST_DIR}/src/bsp_dwt.c
    
  # {{END_TARGET_SOURCES}}
)
