#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "material.h"

typedef struct Sphere {
    Vec3 center;
    float radius;
    Material material;
} Sphere;

Sphere* Sphere_new(Vec3 center, float radius, Material material);
void Sphere_free(Sphere*);

float Sphere_intersect (Sphere*, Vec3 origin, Vec3 dir);
Vec3  Sphere_normal    (Sphere*, Vec3 hitPosition);

#endif

