cmake_minimum_required (VERSION 3.1)
project (WTF C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

function(target_output_directory binary_name target_dir)
    set_target_properties(${binary_name} 
        PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${target_dir}
    )
endfunction(target_output_directory)

# Library
add_library(ctf SHARED 
    src/MathUtils.h
    src/MathUtils.c
    src/Vectors.h
    src/Vectors.c
    src/Quaternions.h
    src/Quaternions.c
    src/Rotations.h
    src/Rotations.c
)
target_link_libraries(ctf m)

# Tests
configure_file(scripts/do_tests.sh tests/do_tests.sh COPYONLY)

add_executable(math_utils_test 
    src/MinTest.h
    src/MathUtilsTest.c
)
target_link_libraries(math_utils_test ctf)
target_output_directory(math_utils_test "tests/")

add_executable(vectors_test 
    src/MinTest.h
    src/VectorsTest.c
)
target_link_libraries(vectors_test ctf)
target_output_directory(vectors_test "tests/")

add_executable(quaternions_test 
    src/MinTest.h
    src/QuaternionsTest.c
)
target_link_libraries(quaternions_test ctf)
target_output_directory(quaternions_test "tests/")

add_executable(rotations_test 
    src/MinTest.h
    src/RotationsTest.c
)
target_link_libraries(rotations_test ctf)
target_output_directory(rotations_test "tests/")

# Examples
add_executable(example 
    examples/main.c
)
target_link_libraries(example SDL2)
include_directories(example, "/usr/include/SDL2")
target_output_directory(example "examples/")
