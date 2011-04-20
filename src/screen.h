#ifndef SCREEN_H
#define SCREEN_H

#include <stdlib.h>
#include "scene.h"

typedef struct Screen {
    size_t width, height, pitch;
    void* pixels;
} Screen;

void Screen_render(Screen* self, Scene* scene);

#endif

