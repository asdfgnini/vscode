
# BSP
file(GLOB_RECURSE BSP_SRCS
    bsp/*.c
)

set(BSP_INCS
    bsp/
)

# APP
file(GLOB_RECURSE APP_SRCS
    app/*.c
)

set(APP_INCS
    app/
)

set(requires
    
    )


idf_component_register(SRCS "main.c" ${BSP_SRCS} ${APP_SRCS}
                        INCLUDE_DIRS "." ${BSP_INCS} ${APP_INCS}
                        REQUIRES ${requires})

