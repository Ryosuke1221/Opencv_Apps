cmake_minimum_required(VERSION 2.8)

project(test_cmake )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "test_opencv" )

add_subdirectory(include_time_string)
add_subdirectory(test_opencv)
add_subdirectory(test_cut)
add_subdirectory(test_black_margin)
add_subdirectory(test_mouse_original)
add_subdirectory(test_black_line)