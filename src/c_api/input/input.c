#include "../input.h"
#include "allegro5/keycodes.h"

#include <stdlib.h>
#include <string.h>

KeyState keystate;

void input_init(void) {
    keystate.keys = malloc(sizeof(bool) * ALLEGRO_KEY_MAX);
    memset(keystate.keys, false, ALLEGRO_KEY_MAX);
}
PARHELIA_EXPORT bool is_key_pressed(int key) {
    return keystate.keys[key];
}
