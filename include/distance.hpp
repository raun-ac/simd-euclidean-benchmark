// distance.hpp

#ifndef DISTANCE_HPP
#define DISTANCE_HPP

#include <cstddef>

float scaler_distance (const float* a, const float* b, size_t size);

float simd_distance (const float* a, const float* b, size_t size);

#endif
