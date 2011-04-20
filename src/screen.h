#ifndef SCREEN_H
#define SCREEN_H

#include <stdlib.h>
#include "scene.h"

typedef struct Screen {
    size_t width, height, pitch;
    void* pixels;
} Screen;

void Screen_render2D(Screen* self, Scene* scene);
void Screen_render3D(Screen* self, Scene* scene);

#endif

