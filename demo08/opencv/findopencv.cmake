set(OPENCV_PATH "G:/opecv4.9/opencv/build" CACHE PATH "the OPENCV PATH")


add_library(OpenCV SHARED IMPORTED GLOBAL)
set(opencv_dll "${OPENCV_PATH}/x64/vc16/bin/opencv_world490d.dll" CACHE INTERNAL "the opencv4.9 dll")

target_include_directories(OpenCV INTERFACE "${OPENCV_PATH}/include/")

set_target_properties(OpenCV 
    PROPERTIES 
        IMPORTED_LOCATION "${OPENCV_PATH}/x64/vc16/bin/opencv_world490d.dll"
        IMPORTED_IMPLIB "${OPENCV_PATH}/x64/vc16/lib/opencv_world490d.lib") 