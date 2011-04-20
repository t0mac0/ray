#include "screen.h"

void Screen_render2D(Screen* self, Scene* scene) {
    Vec3 origin = Vec3_new(0, 0, -5.0f);
    float sy =  0.005f * (float)self->height;
    float sx = -0.005f * (float)self->width;
    float dy = -0.01f;
    float dx =  0.01f;


    float fy = sy;
    for (size_t y = 0; y < self->height; y++, fy += dy) {
        void* pixelrow = ((char*)self->pixels) + y * self->pitch;
        float fx = sx;
        for (size_t x = 0; x < self->width; x++, fx += dx) {
            Vec3 dir = Vec3_normal(Vec3_new(fx, fy, 5.0f));
            ((Color*)pixelrow)[x] = Scene_cast(scene, origin, dir);
        }
    }
}

void Screen_render3D(Screen* self, Scene* scene) {
    Vec3 origin = Vec3_new(0, 0, -5.0f);

    for (size_t y = 0; y < self->height; y++) {
        float fy = 0.01f*(float)y - 0.005f*(float)self->height;
        void* pixelrow = ((char*)self->pixels) + y * self->pitch;
        for (size_t x = 0; x < self->width; x++) {
            float fx = 0.1f*(float)x - 0.05f*(float)self->width;
            Vec3 dir = Vec3_normal(Vec3_new(fx, fy, 5.0f));
            ((Color*)pixelrow)[x] = Scene_cast(scene, origin, dir);
        }
    }
}

