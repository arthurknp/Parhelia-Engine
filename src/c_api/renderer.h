#ifndef RENDERER_H
#define RENDERER_H

#define PARHELIA_EXPORT __declspec(dllexport) 

#include "allegro5/bitmap.h"
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

PARHELIA_EXPORT Color parhelia_create_color_from_ints(int r, int g, int b, int a);

typedef struct {
    ALLEGRO_BITMAP* ptr;
} Texture;

// draw
PARHELIA_EXPORT void parhelia_clear_screen(Color col);
PARHELIA_EXPORT void parhelia_draw_rect(float x, float y, float w, float h, Color col);
PARHELIA_EXPORT void parhelia_swap_buffers(void);

#endif // RENDERER_H