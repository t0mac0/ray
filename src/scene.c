#include <stdlib.h>
#include <stdbool.h>
#include "scene.h"
#include "sphere.h"

struct Scene {
    size_t  num_lights;
    size_t  num_spheres;
    Sphere** lights;
    Sphere** spheres;
};

Scene* Scene_new() {
    Scene* self   = calloc(sizeof *self, 1);
    self->lights  = calloc(sizeof *self->lights,  1);
    self->spheres = calloc(sizeof *self->spheres, 1);
    return self;
}

void Scene_free(Scene* self) {
    for (size_t i = 0; i < self->num_lights; i++)
        Sphere_free(self->lights[i]);
    for (size_t i = 0; i < self->num_spheres; i++)
        Sphere_free(self->spheres[i]);
    free(self);
}

void Scene_addSphere(Scene *self, Sphere* sphere) {
    self->num_spheres += 1;
    self->spheres = realloc(self->spheres,
        self->num_spheres * sizeof(Sphere*)
    );
    self->spheres[self->num_spheres - 1] = sphere;
}

void Scene_addLight(Scene *self, Sphere* light) {
    self->num_lights += 1;
    self->lights = realloc(self->lights,
        self->num_lights * sizeof(Sphere*)
    );
    self->lights[self->num_lights - 1] = light;
}


Color Scene_cast(Scene* self, Vec3 origin, Vec3 dir) {

    float   lightdist = INFINITY;
    Sphere* light     = NULL;
    bool    lightin   = false;
    for (size_t i = 0; i < self->num_lights; i++) {
        float dist = Sphere_intersect(self->lights[i], origin, dir);
        if (dist > 0.0f && dist < lightdist) {
            lightdist = dist;
            light = self->lights[i];
            lightin = false;
        } else if (dist < 0.0f && -dist < lightdist) {
            lightdist = -dist;
            light = self->lights[i];
            lightin = true;
        }
    }

    float   spheredist = INFINITY;
    Sphere* sphere     = NULL;
    bool    spherein   = false;
    for (size_t i = 0; i < self->num_spheres; i++) {
        float dist = Sphere_intersect(self->spheres[i], origin, dir);
        if (dist > 0.0f && dist < spheredist) {
            spheredist = dist;
            sphere = self->spheres[i];
            spherein = false;
        } else if (dist < 0.0f && -dist < spheredist) {
            spheredist = -dist;
            sphere = self->spheres[i];
            spherein = true;
        }
    }

    if (light && lightdist < spheredist) {
        return light->color;
    } else if (sphere) {
        // diffuse me some spheres!!!
        Vec3 hit = Vec3_scale(dir, spheredist);
        Vec3 normal = Sphere_normal(sphere, hit);
        Color result = Color_new(0,0,0);
        for (size_t i = 0; i < self->num_lights; i++) {
            Vec3 lightray = Vec3_sub(self->lights[i]->center, hit);
            lightray = Vec3_normal(lightray);
            float diffusion = Vec3_dot(lightray, normal);
            if (diffusion < 0) continue;
            diffusion *= 0.9; // built-in diffusion constant for now

            Color component = self->lights[i]->color;
            component = Color_mul(sphere->color, component);
            component = Color_scale(component, diffusion);
            result = Color_add(result, component);
        }
        return result;
    } else {
        return Color_new(0,0,0);
    }
}

