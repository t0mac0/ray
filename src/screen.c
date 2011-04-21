#include "screen.h"

#define SEP3D 0.2f
#define SAMPLE 2

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

    float ey  = dy / (float)SAMPLE;
    float ex  = dx / (float)SAMPLE;

    size_t mx = self->width / 2;

    float fy = sy;
    Color ORc = Color_new(0,0,0); 
    Color OLc = Color_new(0,0,0);
    for (size_t y = 0; y < self->height; y++, fy += dy) {
        void* pixelrow = ((char*)self->pixels) + y * self->pitch;
        float fx = sx;
        for (size_t x = 0; x < mx-1; x++, fx += dx) {
            Vec3 dir = Vec3_normal(Vec3_new(fx, fy, 5.0f));
            Color Rc = Scene_cast(scene, originR, dir);
            Color Lc = Scene_cast(scene, originL, dir);

            if (!Color_far(Rc, ORc) && !Color_far(Lc, OLc)) {
                ((Color*)pixelrow)[x]      = Rc;
                ((Color*)pixelrow)[x+mx+1] = Lc;
                ORc = Rc;
                OLc = Lc;
                continue;
            }

            int Rr = 0; int Rg = 0; int Rb = 0;
            int Lr = 0; int Lg = 0; int Lb = 0;

            float sfy = fy;
            for (size_t syi = 0; syi < SAMPLE; syi++, sfy += ey) {
                float sfx = fx;
                for (size_t sxi = 0; sxi < SAMPLE; sxi++, sfx += ex) {
                    Vec3 dir = Vec3_normal(Vec3_new(sfx, sfy, 5.0f));
                    Color Rc = Scene_cast(scene, originR, dir);
                    Color Lc = Scene_cast(scene, originL, dir);
                    Rr += Rc.r; Rg += Rc.g; Rb += Rc.b;
                    Lr += Lc.r; Lg += Lc.g; Lb += Lc.b;
                }
            }

            int SAMPLESQ = SAMPLE*SAMPLE;
            Rr /= SAMPLESQ; Rg /= SAMPLESQ; Rb /= SAMPLESQ;
            Lr /= SAMPLESQ; Lg /= SAMPLESQ; Lb /= SAMPLESQ;

            ((Color*)pixelrow)[x]      = ORc = Color_new(Rr, Rg, Rb);
            ((Color*)pixelrow)[x+mx+1] = OLc = Color_new(Lr, Lg, Lb); 
        }
        ((Color*)pixelrow)[mx] = ((Color*)pixelrow)[mx+1] =
            Color_new(128, 128, 128);
    }
}

