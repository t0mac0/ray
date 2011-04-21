#include "sphere.h"
#include <stdlib.h>

Sphere* Sphere_new(Vec3 center, float radius, Material material) {
    Sphere* self = calloc(sizeof *self, 1);
    self->center = center;
    self->radius = radius;
    self->material = material;
    return self;
}

void Sphere_free(Sphere* self) {
    free(self);
}

// Adapted from Jacco Bikker's raytracing tutorial.
// TODO: come up with a reasonable explanation for this algorithm.
float Sphere_intersect(Sphere* self, Vec3 origin, Vec3 dir) {
    Vec3 v = Vec3_sub(origin, self->center);
    float b = -Vec3_dot(v, dir);
    float det = b*b - Vec3_dot(v, v) + self->radius*self->radius;
    if (det > 0.0f) {
        det = sqrtf(det);
        float i1 = b - det;
        float i2 = b + det;
        if (i2 > 0.0f) {
            if (i1 < 0.0f)
                return -i2; // hit from the inside
            else
                return i1; // hit from the outside
        }
    }
    return 0.0f; // miss
}

Vec3 Sphere_normal(Sphere* self, Vec3 hit) {
    return Vec3_scale(Vec3_sub(hit, self->center),  1.0f/self->radius);
}

