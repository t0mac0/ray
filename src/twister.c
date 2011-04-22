
#include "twister.h"
#include <stdlib.h>

#define DATALEN 624

struct Twister {
    size_t index;
    uint32_t data[DATALEN];
};

Twister* Twister_new(uint32_t seed) {
    Twister *self = malloc(sizeof *self);
    self->index = 0;
    uint32_t last = self->data[0] = seed;
    for (size_t i = 1; i < DATALEN; i++) {
        last = 1812433253 * (last ^ (last >> 30)) + i;
        self->data[i] = last;
    }
    return self;
}

void Twister_free(Twister* self) {
    free(self);
}

void Twister_regen(Twister* self) {
    for (size_t i = 0; i < DATALEN; i++) {
        uint32_t y = self->data[i] & 0x80000000;
        y |= self->data[(i+1)%DATALEN] & 0x7FFFFFF;
        self->data[i] = self->data[(i+397)%DATALEN];
        self->data[i] ^= y >> 1;
        if (y & 1)
            self->data[i] ^= 2567483615;
    }
}

uint32_t Twister_uint32(Twister* self) {
    if (self->index == 0)
        Twister_regen(self);
    uint32_t y = self->data[self->index];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 2636928640);
    y = y ^ ((y << 15) & 4022730752);
    y = y ^ (y >> 18);
    self->index = (self->index + 1) % DATALEN;
    return y;
}

float Twister_float(Twister* self) {
    float f = (float)Twister_uint32(self);
    f /= (float)0xFFFFFFFF; 
    return f;
}




