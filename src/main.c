#define WIDTH  700
#define HEIGHT 400
#define DEPTH  32
#define BPP    4

#include <SDL/SDL.h>

#include "screen.h"
#include "scene.h"

Scene* mkScene() {
    Scene* self = Scene_new();
    Scene_addLight (self, Sphere_new(Vec3_new(-20, 10, 60), 0.4f,
                                     Color_new(255, 255, 200)));
    Scene_addLight (self, Sphere_new(Vec3_new(20, 10, 100), 0.4f,
                                     Color_new(255, 255, 255)));
    Scene_addLight (self, Sphere_new(Vec3_new(0, -100, 0), 0.4f,
                                     Color_new(128, 128, 128)));
    Scene_addLight (self, Sphere_new(Vec3_new(0, 0, -200), 0.4f,
                                     Color_new(128, 128, 128)));
    Scene_addSphere(self, Sphere_new(Vec3_new(5, -5, 75), 10,
                                     Color_new(180, 100, 30)));
    Scene_addSphere(self, Sphere_new(Vec3_new(0, 3, 80), 6,
                                     Color_new(0, 100, 200)));
    Scene_addSphere(self, Sphere_new(Vec3_new(-7, 0, 90), 6,
                                     Color_new(100, 0, 100)));
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
    }

quit:
    SDL_Quit();
}

