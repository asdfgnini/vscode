

aux_source_directory(./src media_src)

file(GLOB_RECURSE media_header ./include)


add_executable(${media_name} ${media_src} ${media_header})

target_include_directories(${media_name} PUBLIC ./include)

target_compile_features(${media_name} PUBLIC cxx_std_17)

target_link_libraries(${media_name} PUBLIC SDL)

