cmake_minimum_required(VERSION 3.28)
project(SIMD_Benchmark VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)

add_executable(simd_bench 
    src/sim_main.cpp 
    src/distance.cpp
)

target_compile_options(simd_bench PRIVATE 
    -O3 
    -mavx512f 
    -fno-tree-vectorize 
    -Wall 
    -Wextra
)