#include <iostream>
#include <chrono>
#include <immintrin.h>


__attribute__((optimize("no-tree-vectorize")))
float scaler_distance (const float* a, const float* b, size_t size) {
    float sc_res = 0.0f;
    for (size_t i = 0; i < size; i++) {
        float diff = a[i] - b[i];
        sc_res += diff * diff;
    }

    return sc_res;
}


float simd_distance (const float* a, const float* b, size_t size) {

    __m512 sum_vec = _mm512_setzero_ps();

    for (size_t i = 0; i < size; i += 16) {

        __m512 vec_a = _mm512_loadu_ps(&a[i]);
        __m512 vec_b = _mm512_loadu_ps(&b[i]);

        __m512 vec_diff = _mm512_sub_ps(vec_a, vec_b);

        sum_vec = _mm512_add_ps(sum_vec, _mm512_mul_ps(vec_diff, vec_diff));
    }

    return _mm512_reduce_add_ps(sum_vec);
}






int main() {

    const size_t N = 64 * 189;

    float* a = (float*)aligned_alloc(64, (N * sizeof(float)));
    float* b = (float*)aligned_alloc(64, (N * sizeof(float)));

    for (size_t i = 0; i < N; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    float trial1 = scaler_distance(a, b, N);
    float trial2 = simd_distance(a, b, N);


    //Measuring Time for Scaler Function
    auto start = std::chrono::high_resolution_clock::now();
    float res_s = scaler_distance(a, b, N);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> scaler_ms = end - start;


    //Measuring Time for SIMD function
    start = std::chrono::high_resolution_clock::now();
    float res_av = simd_distance(a, b, N);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> simd_dist_ms = end - start;

    std::cout << "Scaler Result = " << res_s << " | Time = " << scaler_ms.count() << " ms" << std::endl;
    std::cout << "SIMD Result = " << res_av << " | Time = " << simd_dist_ms.count() << " ms" << std::endl;
}