#define WIDTH  700
#define HEIGHT 400
#define DEPTH  32
#define BPP    4

#include <SDL/SDL.h>

#include <stdbool.h>
#include "screen.h"
#include "scene.h"

Scene* mkScene() {
    Scene* self = Scene_new();
    Scene_addLight (self, Sphere_new(Vec3_new(-20, 10, 60), 0.4f,
                  Material_new(255, 255, 255, 0, 0, 0, 0, 0)));
    Scene_addLight (self, Sphere_new(Vec3_new(30, 15, 100), 0.4f,
                  Material_new(255, 255, 255, 0, 0, 0, 0, 0)));
    Scene_addSphere(self, Sphere_new(Vec3_new(5, -5, 75), 10,
                  Material_new(180, 100, 30, 0.2, 0.4, 0.7, 0.5, 1.04f)));
    Scene_addSphere(self, Sphere_new(Vec3_new(-10, -10, 40), 3,
                  Material_new(0, 100, 200, 0.5, 0, 0, 0.9, 1.03f)));
    Scene_addSphere(self, Sphere_new(Vec3_new(-15, 0, 75), 6,
                  Material_new(250, 250, 250, 0.3, 0.5, 0.8, 0, 0)));
    Scene_addSphere(self, Sphere_new(Vec3_new(-7, -55, 80), 40,
                  Material_new(0, 100, 100, 0.9, 0.2, 0, 0, 0)));
    Scene_addSphere(self, Sphere_new(Vec3_new(0, 100, 500), 200,
                  Material_new(250, 250, 250, 0, 0.5, 0.9, 0, 0)));
    for (int j = 0; j < 4; j++) {
        float y = -35 + j*20;
        for (int i = 0; i < 7; i++) {
            float x = -55 + i*20;
            Scene_addSphere(self, Sphere_new(Vec3_new(x, y, 200), 8,
                          Material_new(250, 50, 50, 0.9f, 0, 0, 0, 0)));
        }
    }
    return self;
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH,
        SDL_HWSURFACE);

    SDL_Event event;

    Screen rscreen = {
        .width  = WIDTH,
        .height = HEIGHT,
        .pitch  = WIDTH*BPP
    };
    Scene *scene = mkScene();
    Sphere *moving = Sphere_new(Vec3_new(20, 15, 70), 5.0f,
                Material_new(100, 180, 100, 0.3, 0.7, 0.4, 0, 0));
    Scene_addSphere(scene, moving);
    bool movingLeft = true;

    while(1) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                    goto quit;
            }
        }
        SDL_LockSurface(screen);
        rscreen.pixels = screen->pixels;
        Screen_render3D(&rscreen, scene);
        SDL_UnlockSurface(screen);
        SDL_Flip(screen);

        if (movingLeft) {
            moving->center.x -= 1.0f;
            if (moving->center.x < -20.0f)
                movingLeft = false;
        } else {
            moving->center.x += 1.0f;
            if (moving->center.x > 20.0f)
                movingLeft = true;
        }

    }

quit:
    SDL_Quit();
}

