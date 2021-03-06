#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <stdbool.h>


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
        .b = b,
        ._ignore_ = 0
    };
    return result;
}

#define bindcolor(v) ((v) >= 255 ? 255 : ((v) <= 0 ? 0 : (v)))

static inline Color Color_add(Color a, Color b) {
    return Color_new(
        bindcolor((int)a.r + (int)b.r),
        bindcolor((int)a.g + (int)b.g),
        bindcolor((int)a.b + (int)b.b)
    );
}

static inline Color Color_scale(Color a, float k) {
    return Color_new(
        bindcolor((int)((float)a.r * k)),
        bindcolor((int)((float)a.g * k)),
        bindcolor((int)((float)a.b * k))
    );
}

static inline Color Color_mul(Color a, Color b) {
    return Color_new(
        bindcolor(((int)a.r * (int)b.r) / 255),
        bindcolor(((int)a.g * (int)b.g) / 255),
        bindcolor(((int)a.b * (int)b.b) / 255)
    );
}

#define FARNESS 16
static inline bool Color_far(Color a, Color b) {
    return (a.r - b.r > FARNESS) || (b.r - a.r > FARNESS) ||
           (a.g - b.g > FARNESS) || (b.g - a.g > FARNESS) ||
           (a.b - b.b > FARNESS) || (b.b - a.b > FARNESS);
}

#endif

