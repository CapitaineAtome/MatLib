cmake_minimum_required(VERSION 3.15)

project(MatLib CXX)

set(CMAKE_CXX_STANDARD 23)

include_directories(../sources)

add_executable(VectorTest
        vector_test.cpp
        )

add_executable(MatrixTest
        matrix_test.cpp
        )