#include <benchmark/benchmark.h>
#include <cstdlib>
#include "distance.hpp"

static void CustomArguments(benchmark::Benchmark* b) {

    for (int i = 1024; i <= 8388608; i*=4) {
        b->Arg(i);
    }
}


static void BM_ScalarDistance(benchmark::State& state) {

    size_t N = state.range(0);
    float* a = (float*)aligned_alloc(64, N*sizeof(float));
    float* b = (float*)aligned_alloc(64, N*sizeof(float));

    for (size_t i = 0; i < N; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    for (auto _ : state) {

        benchmark::DoNotOptimize(scaler_distance(a, b, N));
    }

    free(a);
    free(b);
}

BENCHMARK(BM_ScalarDistance)->Apply(CustomArguments);


// here we are benchmarking the simd_distance function
static void BM_SIMDDistance(benchmark::State& state) {

    size_t N = state.range(0);
    float* a = (float*)aligned_alloc(64, N*sizeof(float));
    float* b = (float*)aligned_alloc(64, N*sizeof(float));

    for (size_t i = 0; i < N; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(simd_distance(a, b, N));
    }

    free(a);
    free(b);
}

BENCHMARK(BM_SIMDDistance)->Apply(CustomArguments);

BENCHMARK_MAIN();