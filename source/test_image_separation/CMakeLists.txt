add_executable(test_image_separation test_image_separation.cpp)

find_package( OpenCV REQUIRED PATHS "C:/Program Files/OpenCV-3.4.1")

include_directories(${OpenCV_INCLUDE_DIRS} )
include_directories("${CMAKE_SOURCE_DIR}/include_time_string")

target_link_libraries(test_image_separation ${OpenCV_LIBS} )
target_link_libraries(test_image_separation time_string)