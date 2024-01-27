
file(GLOB SRC_FILE ./src/*.cu)
file(GLOB HEADER_FILE ./include/*.cuh)


add_executable(${PROJECT_NAME} main.cu ${SRC_FILE} ${HEADER_FILE})

