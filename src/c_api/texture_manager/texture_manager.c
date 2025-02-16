#include "../texture_manager.h"
#include "allegro5/bitmap.h"
#include "allegro5/bitmap_io.h"
#include <stdio.h>
#include <allegro5/allegro_memfile.h>

#include <assert.h>

#include "../error_texture.h"

TextureManager globalTextureManager;

void create_global_texture_manager(void){
    globalTextureManager = (TextureManager) {0};
    globalTextureManager.items = malloc(sizeof(ALLEGRO_BITMAP*) * INITIAL_TEXTURE_ARRAY_SIZE);
    
    assert(globalTextureManager.items != NULL && "Erro ao criar array do texture manager");

    globalTextureManager.capacity = INITIAL_TEXTURE_ARRAY_SIZE;
    globalTextureManager.used = 0;
}

void destroy_global_texture_manager(void) {
    free(globalTextureManager.items);
}

void parhelia_texture_manager_load_error_texture(void) {
    ALLEGRO_BITMAP* bitmap;

    ALLEGRO_FILE* file = al_open_memfile((void*)image_data, image_size, "rb");
    assert(file != NULL && "Erro ao carregar textura de erro");

    bitmap = al_load_bitmap_f(file, ".bmp");

    int idx = globalTextureManager.used++;
    assert(idx == 0 && "Indice da textura de erro DEVE ser 0, carregou alguma textura antes?");
    // chegar se não chegou no limite do array
    if (idx >= globalTextureManager.capacity) {
        size_t newCap = globalTextureManager.capacity * TEXTURE_ARRAY_GROWTH_FACTOR;
        realloc(globalTextureManager.items, sizeof(ALLEGRO_BITMAP*) * newCap);
        globalTextureManager.capacity = newCap;
        assert(globalTextureManager.items != NULL && "Erro ao reallocar array do Texture mamager");
    }

    globalTextureManager.items[idx] = bitmap;

    al_fclose(file);
}

Texture parhelia_texture_manager_load_texture(const char* path) {
    assert(globalTextureManager.items != NULL && "globalTextureManager não inicializado");

    ALLEGRO_BITMAP* bitmap = al_load_bitmap(path);
    if (bitmap == NULL) {
        fprintf(stderr, "Não foi possível carregar textura %s, utilizando textura fallback.\n", path);
        return 0;
    }
    int idx = globalTextureManager.used++;
    // chegar se não chegou no limite do array
    if (idx >= globalTextureManager.capacity) {
        size_t newCap = globalTextureManager.capacity * TEXTURE_ARRAY_GROWTH_FACTOR;
        realloc(globalTextureManager.items, sizeof(ALLEGRO_BITMAP*) * newCap);
        globalTextureManager.capacity = newCap;
        assert(globalTextureManager.items != NULL && "Erro ao reallocar array do Texture mamager");
    }

    globalTextureManager.items[idx] = bitmap;
    return idx;
}

bool parhelia_texture_manager_is_texture_valid(Texture t) {
    if (t >= globalTextureManager.used) {
        return false;
    } else {
        return true;
    }
}
