#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "sphere.h"
#include "color.h"
#include "vec3.h"

typedef struct Scene Scene;

Scene* Scene_new();
void   Scene_free(Scene* self);

// Set up
void Scene_addLight (Scene* self, Sphere* light);
void Scene_addSphere(Scene* self, Sphere* sphere);

// Use
Color Scene_cast (Scene* self, Vec3 origin, Vec3 dest);
Color Scene_cast_(Scene* self, Vec3 origin, Vec3 dest,
    float rindex, int depth);
bool Scene_shadow(Scene* self, Vec3 origin, Vec3 dir, float lightdist);

#endif

