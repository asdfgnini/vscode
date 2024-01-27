
aux_source_directory(./src SRC_FILE)
message("SRC_FILE: ${SRC_FILE}")
file(GLOB HEADER_FILE ./include/*h)
message("HEADER_FILE: ${HEADER_FILE}")
add_executable(${PROJECT_NAME} main01.cpp ${SRC_FILE} ${HEADER_FILE})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_include_directories(${PROJECT_NAME} PUBLIC "G:\\boost_1_84_0")
target_link_directories(${PROJECT_NAME} PUBLIC "G:\\boost_1_84_0\\stage\\lib")

target_compile_options(${PROJECT_NAME} PUBLIC -D_WIN32_WINNT=0x0601)