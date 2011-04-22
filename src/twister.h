#ifndef TWISTER_H
#define TWISTER_H

#include <stdint.h>

typedef struct Twister Twister;

Twister* Twister_new(uint32_t seed);
void     Twister_free(Twister*);
uint32_t Twister_uint32(Twister*);
float    Twister_float(Twister*);

#endif

