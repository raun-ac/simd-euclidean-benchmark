#include <immintrin.h>
#include "distance.hpp"





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