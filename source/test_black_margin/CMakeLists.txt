add_executable(test_black_margin test_black_margin.cpp)

find_package( OpenCV REQUIRED PATHS "C:/Program Files/OpenCV-3.4.1")

include_directories(${OpenCV_INCLUDE_DIRS} )

target_link_libraries(test_black_margin ${OpenCV_LIBS} )