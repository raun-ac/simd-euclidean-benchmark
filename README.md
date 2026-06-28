
![Logo](https://github.com/raun-ac/simd-euclidean-benchmark/blob/Main/docs/img/logo.png?raw=true)


# SIMD AVX-512 Memory Wall Benchmark

An empirical demonstration of the Von Neumann bottleneck, measuring the decrease in performance of AVX-512 vectorized mathematical operations as data sizes exceed CPU cache boundaries (L1/L2/L3).


## The Experiment

This project calculates the Euclidean distance between two dense vectors using pure scalar C++ versus AVX-512 hardware intrinsics. While AVX-512 offers a theoretical 16x speed up for 32-bit floats, real-world speedup is strictly bounded by memory bandwidth.

By increasing the array size N from 1,024 to 8,388,608 elements, this benchmark explicitly maps the hardware cache boundaries of an Intel Ice Lake architecture, proving that computational optimization is irrelevant if the CPU is starved for data.
## The Memory Wall

SIMD Performance vs Memory Bottleneck

![Logo](https://github.com/raun-ac/simd-euclidean-benchmark/blob/Main/docs/img/memory_wall_graph.png?raw=true)
Generated on Intel Ice Lake using Google Benchmark. Lower arrays fit in fast cache; larger arrays force slow RAM fetches
## Raw Output

![App Screenshot](https://github.com/raun-ac/simd-euclidean-benchmark/blob/Main/docs/img/raw_output.png?raw=true)


## Conclusion

Once the memory footprint exceeds the L3 cache, the 18x computational advantage of AVX-512 plummets to 2.1x due to RAM latency. The system becomes memory-bound, not compute-bound
## Test Platform

Operating System : Ubuntu 24.04.1

Compiler : g++ 13.3.0

CPU: Intel Core i3-1005G1 (Ice Lake)

Build System: CMake 3.28
## Run Locally

Ensure that you are on a linux machine with an AVX-512 capable CPU.

Clone the project

```bash
  git clone https://github.com/raun-ac/simd-euclidean-benchmark.git
```

Go to the project directory

```bash
  cd simd-euclidean-benchmark
```

Configure a Release build (Strips debug bloat for accurate timing)

```bash
  mkdir build && cd build
  cmake -DCMAKE_BUILD_TYPE=Release ..
```

Compile the binary

```bash
  make
```


## Reproducing the Data

To run the benchmark and generate the raw JSON timings on your specific CPU architecture. Go to the build directory and run the following command 

```bash
  ./simd_bench --benchmark_format=json > results.json
```
To plot the cache boundary graph, go to the root directory and enter in a virutal environment by running the following command (make sure python3 is already installed)

```bash
  source .venv/bin/activate
```
Install the required python libraries by running the following command

```bash
  pip install -r scripts/requirements.txt
```
After that, run the python script in the directory to generate the graph

```bash
  python3 scripts/plot_result_data.py
```
The graph image will be generated and stored in docs/img/

## Architecture


`include/distance.hpp` : Function prototypes

`src/distance.cpp` : The scalar and AVX-512 function implementations

`src/sim_main.cpp` : Google Benchmark configurations and setup

`scripts/plot_result_data.py` : Python data visualization script 




