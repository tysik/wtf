cmake_minimum_required (VERSION 3.1)
project ("Weird TransFormations" C)

set(LIB_NAME "wtf")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic")

function(target_output_directory binary_name target_dir)
    set_target_properties(${binary_name} 
        PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${target_dir}
    )
endfunction(target_output_directory)

# Library
add_library(${LIB_NAME} SHARED 
    src/MathUtils.h
    src/MathUtils.c
    src/Vector.h
    src/Vector.c
    src/Quaternion.h
    src/Quaternion.c
    src/Rotation.h
    src/Rotation.c
)
target_link_libraries(${LIB_NAME} m)

# Tests
# TODO: Use ctest
configure_file(scripts/do_tests.sh tests/do_tests.sh COPYONLY)

add_executable(math_utils_test src/MathUtilsTest.c)
target_link_libraries(math_utils_test ${LIB_NAME})
target_output_directory(math_utils_test "tests/")

add_executable(vector_test src/VectorTest.c)
target_link_libraries(vector_test ${LIB_NAME})
target_output_directory(vector_test "tests/")

add_executable(quaternion_test src/QuaternionTest.c)
target_link_libraries(quaternion_test ${LIB_NAME})
target_output_directory(quaternion_test "tests/")

add_executable(rotations_test src/RotationTest.c)
target_link_libraries(rotations_test ${LIB_NAME})
target_output_directory(rotations_test "tests/")

# Examples
add_executable(example 
    examples/main.c
)
target_link_libraries(example SDL2)
target_output_directory(example "examples/")
