#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

typedef struct Material Material;
struct Material {
    Color color;
    float diffusion;
    float specular;
    float reflection;
    float refraction;
    float refrindex;
};

static inline Material Material_new(
    float r, float g, float b,
    float diffusion,
    float specular,
    float reflection,
    float refraction,
    float refrindex
) {
    Material result = {
        .color = Color_new(r, g, b),
        .diffusion  = diffusion,
        .specular   = specular,
        .reflection = reflection,
        .refraction = refraction,
        .refrindex = refrindex
    };
    return result;
}

#endif

