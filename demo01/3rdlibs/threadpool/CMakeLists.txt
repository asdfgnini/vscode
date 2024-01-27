add_library(threadpool INTERFACE)
target_include_directories(threadpool INTERFACE ./)
target_compile_features(threadpool INTERFACE cxx_std_17)
