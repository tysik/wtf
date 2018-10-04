cmake_minimum_required (VERSION 3.1)
project (CTFs C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# find_package(OpenMP)
# if(OPENMP_FOUND)
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# endif()

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
# add_executable(math_utils_test 
#     src/MinTest.h
#     src/MathUtilsTest.c
# )
# target_link_libraries(math_utils_test ctf)

# add_executable(vectors_test 
#     src/MinTest.h
#     src/VectorsTest.c
# )
# target_link_libraries(vectors_test ctf)

# add_executable(quaternions_test 
#     src/MinTest.h
#     src/QuaternionsTest.c
# )
# target_link_libraries(quaternions_test ctf)

# add_executable(rotations_test 
#     src/MinTest.h
#     src/RotationsTest.c
# )
# target_link_libraries(rotations_test ctf)
