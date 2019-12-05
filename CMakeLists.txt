cmake_minimum_required (VERSION 3.1)
project ("Weird TransFormations" C)

set(LIB_NAME "wtf")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic")

option(BUILD_TESTING "Build unit tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

function(target_output_directory binary dir)
    set_target_properties(${binary} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${dir})
endfunction()

function(add_new_test target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} ${LIB_NAME})
    target_output_directory(${target} tests)
    add_test(${target} tests/${target})
endfunction()

function(add_new_example target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} ${LIB_NAME} SDL2)
    target_output_directory(${target} examples)
endfunction()

add_library(${LIB_NAME} SHARED 
    src/MathUtils.c
    src/Vector.c
    src/Quaternion.c
    src/Rotation.c
)
target_link_libraries(${LIB_NAME} m)
# TODO: Extract public headers

include(CTest)
enable_testing()
if(BUILD_TESTING)
    add_new_test(math_utils_test src/MathUtilsTest.c)
    add_new_test(vector_test src/VectorTest.c)
    add_new_test(quaternion_test src/QuaternionTest.c)
    add_new_test(rotation_test src/RotationTest.c)
endif()

if(BUILD_EXAMPLES)
    add_new_example(example examples/main.c)
endif()