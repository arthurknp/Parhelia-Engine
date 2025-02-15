#ifndef TYPES_H
#define TYPES_H

#include "allegro5/bitmap.h"
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define PARHELIA_EXPORT __declspec(dllexport) 

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

typedef struct {
    ALLEGRO_BITMAP* ptr;
} Texture;


#endif // TYPES_H