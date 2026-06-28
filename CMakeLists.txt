cmake_minimum_required(VERSION 3.28)
project(SIMD_Benchmark VERSION 1.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.5
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests")
FetchContent_MakeAvailable(benchmark)


include_directories(include)

add_executable(simd_bench 
    src/sim_main.cpp 
    src/distance.cpp
)

target_link_libraries(simd_bench PRIVATE benchmark::benchmark pthread)

target_compile_options(simd_bench PRIVATE 
    -O3 
    -mavx512f 
    -fno-tree-vectorize 
    -Wall 
    -Wextra
)