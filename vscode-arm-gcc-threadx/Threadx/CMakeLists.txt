

# 平台相关宏定义
ADD_DEFINITIONS(
  -DTX_ENABLE_FPU_SUPPORT # 不使用 RTOS
  -DTX_ENABLE_STACK_CHECKING
)

add_subdirectory(Port)

add_subdirectory(Src)