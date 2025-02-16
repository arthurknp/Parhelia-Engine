#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "allegro5/bitmap.h"
#include <stdlib.h>

#define INITIAL_TEXTURE_ARRAY_SIZE 128
#define TEXTURE_ARRAY_GROWTH_FACTOR 2

typedef int Texture; // nada mais que um indice

// 0 vai ser uma textura padrao que vai ser usada caso a textura solicitada não consiga ser carregada com exito
typedef struct {
    ALLEGRO_BITMAP** items;
    size_t capacity;
    size_t used;
} TextureManager;

extern TextureManager globalTextureManager;

void create_global_texture_manager(void);
void destroy_global_texture_manager(void);

Texture parhelia_texture_manager_load_texture(const char* path);
bool parhelia_texture_manager_is_texture_valid(Texture t);
void parhelia_texture_manager_load_error_texture(void);

#endif // TEXTURE_MANAGER_H