cmake_minimum_required (VERSION 3.1)
project (QuaternionsC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(quaternions SHARED src/Quaternions.c)
target_link_libraries(quaternions m)

add_library(vectors SHARED src/Vectors.c)
target_link_libraries(vectors m)

add_executable(quaternions_test src/QuaternionsTest.c)
target_link_libraries(quaternions_test quaternions)

add_executable(vectors_test src/VectorsTest.c)
target_link_libraries(vectors_test vectors)