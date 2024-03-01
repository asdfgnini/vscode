
add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_include_directories(${PROJECT_NAME} PUBLIC "G:\\boost_1_84_0")
target_link_directories(${PROJECT_NAME} PUBLIC "G:\\boost_1_84_0\\stage\\lib")
target_compile_options(${PROJECT_NAME} PUBLIC -D_WIN32_WINNT=0x0601)