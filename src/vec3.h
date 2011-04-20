#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct Vec3 Vec3;

struct Vec3 {
    float x;
    float y;
    float z;
};

static inline Vec3 Vec3_new(float x, float y, float z) {
    Vec3 result = {
        .x = x,
        .y = y,
        .z = z
    };
    return result;
}

static inline Vec3 Vec3_add(Vec3 a, Vec3 b) {
    Vec3 result = {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };
    return result;
}

static inline Vec3 Vec3_sub(Vec3 a, Vec3 b) {
    Vec3 result = {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z
    };
    return result;
}

static inline Vec3 Vec3_scale(Vec3 a, float k) {
    Vec3 result = {
        .x = a.x * k,
        .y = a.y * k,
        .z = a.z * k
    };
    return result;
}

static inline Vec3 Vec3_cross(Vec3 a, Vec3 b) {
    Vec3 result = {
        .x = a.y*b.z - b.y*a.z,
        .y = a.z*b.x - b.z*a.x,
        .z = a.x*b.y - b.x*a.y
    };
    return result;
}

static inline float Vec3_dot(Vec3 a, Vec3 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

static inline float Vec3_mag(Vec3 a) {
    return sqrtf(Vec3_dot(a, a));
}

static inline Vec3 Vec3_normal(Vec3 a) {
    float imag = 1.0f / Vec3_mag(a);
    return Vec3_scale(a, imag);
}

#endif

