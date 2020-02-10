add_executable(test_mouse_original test_mouse_original.cpp)

find_package( OpenCV REQUIRED PATHS "C:/Program Files/OpenCV-3.4.1")

include_directories(${OpenCV_INCLUDE_DIRS} )

target_link_libraries(test_mouse_original ${OpenCV_LIBS} )