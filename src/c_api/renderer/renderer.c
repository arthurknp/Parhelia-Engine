#include "../renderer.h"
#include "allegro5/color.h"
#include "allegro5/display.h"
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

uint8_t clamp(int i) {
    if (i <= 0) {
        return 0;
    } else if (i >= UINT8_MAX) {
        return UINT8_MAX;
    } else {
        return i;
    }
}

PARHELIA_EXPORT Color parhelia_create_color_from_ints(int r, int g, int b, int a) {
    Color c = {0};
    c.r = clamp(r);
    c.g = clamp(g);
    c.b = clamp(b);
    c.a = clamp(a);

    return c;
}

PARHELIA_EXPORT void parhelia_draw_rect(float x, float y, float w, float h, Color col) {
    al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgba(col.r, col.g, col.b, col.a));
}

PARHELIA_EXPORT void parhelia_clear_screen(Color col) {
    al_clear_to_color(al_map_rgba(col.r, col.g, col.b, col.a));
}

PARHELIA_EXPORT void parhelia_swap_buffers(void) {
    al_flip_display();
}