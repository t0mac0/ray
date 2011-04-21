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

Color Scene_cast (Scene* self, Vec3 origin, Vec3 dir) {
    return Scene_cast_(self, origin, dir, 4);
}

Color Scene_cast_(Scene* self, Vec3 origin, Vec3 dir, int depth) {
    if (depth == 0)
        return Color_new(0, 0, 0);

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

    Vec3 hit, normal;
    Material material;

    // which primitive was hit?
    if (light && lightdist < spheredist) {
        return light->material.color;
    } else if (sphere) {
        hit = Vec3_add(Vec3_scale(dir, spheredist), origin);
        normal = Sphere_normal(sphere, hit);
        material = sphere->material;
    } else {
        return Color_new(30,30,30);
    }

    Color result = Color_new(0,0,0);
    
    // diffusion
    if (material.diffusion > 0 || material.specular > 0) {
        for (size_t i = 0; i < self->num_lights; i++) {
            Vec3  lightray = Vec3_sub(self->lights[i]->center, hit);
            float lightdist = Vec3_mag(lightray);
            Vec3  lightdir  = Vec3_scale(lightray, 1.0f/lightdist);
            float diffusion = Vec3_dot(lightdir, normal);
            diffusion *= material.diffusion;
            if (Scene_shadow(self, hit, lightdir, lightdist)) continue;
            if (diffusion > 0) {
                Color component = self->lights[i]->material.color;
                component = Color_mul   (component, material.color);
                component = Color_scale (component, diffusion);
                result = Color_add(result, component);
            }

            // specular.
            if (material.specular > 0) {
                Vec3 lightrefl = Vec3_scale(normal,
                           2.0f * Vec3_dot(lightdir, normal));
                lightrefl = Vec3_sub(lightdir, lightrefl);
                float spec = Vec3_dot(dir, lightrefl);
                if (spec > 0) {
                    spec = powf(spec, 20) * material.specular;
                    Color component = Color_scale(material.color, spec);
                    result = Color_add(result, component);
                }
            }
        }
    }

    
    // calculate reflection
    if (material.reflection > 0) {
        Vec3 reflected = Vec3_scale(normal, 2 * Vec3_dot(normal, dir));
        reflected = Vec3_sub(dir, reflected);
        Vec3 rorigin = Vec3_add(hit,Vec3_scale(reflected, 0.001f));
        Color component = Scene_cast_(self, rorigin, reflected, depth-1);
        component = Color_mul   (component, material.color);
        component = Color_scale (component, material.reflection);
        result = Color_add(result, component);
    }

    return result;
}


bool Scene_shadow(Scene* self, Vec3 origin, Vec3 dir, float lightdist) {
    for (size_t i = 0; i < self->num_spheres; i++) {
        float dist = Sphere_intersect(self->spheres[i], origin, dir);
        if ((dist > 0.0f) && (dist < lightdist))
            return true;
    }
    return false;
}



