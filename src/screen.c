#include "screen.h"

#define SEP3D 0.5f

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
    Vec3 originL = Vec3_new(-SEP3D, 0, -5.0f);
    Vec3 originR = Vec3_new( SEP3D, 0, -5.0f);

    float sy =  0.005f * (float)self->height;
    float sx = -0.0025f * (float)self->width;
    float dy = -0.01f;
    float dx =  0.01f;

    size_t mx = self->width / 2;

    float fy = sy;
    for (size_t y = 0; y < self->height; y++, fy += dy) {
        void* pixelrow = ((char*)self->pixels) + y * self->pitch;
        float fx = sx;
        for (size_t x = 0; x < mx-1; x++, fx += dx) {
            Vec3 dir = Vec3_normal(Vec3_new(fx, fy, 5.0f));
            ((Color*)pixelrow)[x]    = Scene_cast(scene, originR, dir);
            ((Color*)pixelrow)[x+mx+1] = Scene_cast(scene, originL, dir);
        }
        ((Color*)pixelrow)[mx] = ((Color*)pixelrow)[mx+1] =
            Color_new(128, 128, 128);
    }
}

