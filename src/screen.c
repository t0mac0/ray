#include "screen.h"

void Screen_render(Screen* self, Scene* scene) {
    Vec3 origin = Vec3_new(0, 0, -5.0f);

    for (size_t y = 0; y < self->height; y++) {
        float fy = 0.1f*(float)y - 0.05f*(float)self->height;
        void* pixelrow = ((char*)self->pixels) + y * self->pitch;
        for (size_t x = 0; x < self->width; x++) {
            float fx = 0.1f*(float)x - 0.05f*(float)self->width;
            Vec3 dir = Vec3_normal(Vec3_new(fx, fy, 5.0f));
            ((Color*)pixelrow)[x] = Scene_cast(scene, origin, dir);
        }
    }
}

