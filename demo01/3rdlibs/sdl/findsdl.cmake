
set(SDL_PATH "G:/SDL2_2.28.5_vc" CACHE PATH "the sdl path")

add_library(SDL SHARED IMPORTED GLOBAL)
set(sdl "G:/SDL2_2.28.5_vc/lib/x64/SDL2.dll" CACHE INTERNAL "the sdl dll")

target_include_directories(SDL INTERFACE "${SDL_PATH}/include")

set_target_properties(SDL 
    PROPERTIES 
        IMPORTED_LOCATION "${SDL_PATH}/lib/x64/SDL2.dll"
        IMPORTED_IMPLIB "${SDL_PATH}/lib/x64/SDL2main.lib"# 和mingw一样这里顺序不可更改    
        IMPORTED_IMPLIB "${SDL_PATH}/lib/x64/SDL2.lib") 