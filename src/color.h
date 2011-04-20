#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef struct Color Color;

#ifdef BIG_ENDIAN
struct Color {
    uint8_t _ignore_;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
#else
struct Color {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t _ignore_;
};
#endif

static inline Color Color_new(uint8_t r, uint8_t g, uint8_t b) {
    Color result = {
        .r = r,
        .g = g,
        .b = b
    };
    return result;
}

#endif

