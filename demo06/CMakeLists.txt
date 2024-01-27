cmake_minimum_required(VERSION 3.16)
project(${CURRENT_FOLDER} LANGUAGES CUDA CXX)

# file
file(GLOB CU_FILES "*.cu")
file(GLOB CPP_FILES "*.cpp")

# target
add_executable(${PROJECT_NAME} ${CPP_FILES} ${CU_FILES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_include_directories(${PROJECT_NAME} PUBLIC "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v12.3\\include")


