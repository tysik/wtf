cmake_minimum_required (VERSION 3.1)
project (QuaternionsC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Libraries
add_library(math_utils SHARED src/MathUtils.c)
target_link_libraries(math_utils m)

add_library(vectors SHARED src/Vectors.c)
target_link_libraries(vectors math_utils)

add_library(quaternions SHARED src/Quaternions.c)
target_link_libraries(quaternions math_utils)

# Tests
add_executable(math_utils_test src/MathUtilsTest.c)
target_link_libraries(math_utils_test math_utils)

add_executable(vectors_test src/VectorsTest.c)
target_link_libraries(vectors_test vectors)

add_executable(quaternions_test src/QuaternionsTest.c)
target_link_libraries(quaternions_test quaternions)
