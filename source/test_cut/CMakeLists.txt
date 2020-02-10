add_executable(test_cut test_cut.cpp)

find_package( OpenCV REQUIRED PATHS "C:/Program Files/OpenCV-3.4.1")

include_directories(${OpenCV_INCLUDE_DIRS} )
include_directories("${CMAKE_SOURCE_DIR}/include_time_string")

target_link_libraries(test_cut ${OpenCV_LIBS} )
target_link_libraries(test_cut time_string)