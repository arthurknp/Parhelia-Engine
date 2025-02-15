#ifndef INPUT_H
#define INPUT_H

#include <allegro5/keycodes.h>
#include <stdbool.h>

#define PARHELIA_EXPORT __declspec(dllexport)

typedef struct {
    bool* keys;
} KeyState;

void input_init(void);
extern KeyState keystate;

PARHELIA_EXPORT bool is_key_pressed(int key);

#endif //  INPUT_H