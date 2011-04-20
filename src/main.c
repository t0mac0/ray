#define WIDTH  200
#define HEIGHT 200
#define DEPTH  32
#define BPP    4

#include <SDL/SDL.h>

#include "screen.h"
#include "scene.h"

Scene* mkScene() {
    Scene* self = Scene_new();
    Scene_addLight (self, Sphere_new(Vec3_new(-5, 5, 10), 3,
                                     Color_new(255, 255, 200)));
    Scene_addLight (self, Sphere_new(Vec3_new(5, -5, 15), 6,
                                     Color_new(180, 100, 30)));
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
        Screen_render(&rscreen, scene);
        SDL_UnlockSurface(screen);
        SDL_Flip(screen);
    }

quit:
    SDL_Quit();
}
