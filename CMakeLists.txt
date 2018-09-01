cmake_minimum_required (VERSION 3.1)
project (QuaternionsC)

add_library(quaternions SHARED src/Quaternions.c)

add_executable(quaternions_test src/QuaternionsTest.c)
target_link_libraries(quaternions_test quaternions)