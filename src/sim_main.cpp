#include <iostream>
#include <chrono>
#include "distance.hpp"





int main() {

    const size_t N = 1024 * 1024;

    float* a = (float*)aligned_alloc(64, (N * sizeof(float)));
    float* b = (float*)aligned_alloc(64, (N * sizeof(float)));

    for (size_t i = 0; i < N; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    //float trial1 = scaler_distance(a, b, N);
    //float trial2 = simd_distance(a, b, N);


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