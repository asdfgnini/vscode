cmake_minimum_required(VERSION 3.22)

add_library(Driver INTERFACE)

target_compile_definitions(Driver INTERFACE 
    USE_STDPERIPH_DRIVER 
    STM32F429_439xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(Driver INTERFACE
    ./STM32F4xx_StdPeriph_Driver/inc
    ./CMSIS/Device/ST/STM32F4xx/Include
    ./CMSIS/Include
)

target_sources(
  Driver
  INTERFACE # {{BEGIN_TARGET_SOURCES}}
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/misc.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cec.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dfsdm.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dsi.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash_ramfunc.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmc.c
          # ${CMAKE_CURRENT_LIST_DIR}/src/stm32f4xx_fsmc.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmpi2c.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_lptim.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spdifrx.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
          ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c
          # {{END_TARGET_SOURCES}}
)

target_link_directories(Driver INTERFACE

)

target_link_libraries(Driver INTERFACE

)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
