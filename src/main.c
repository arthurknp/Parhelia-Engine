#include <windows.h>

#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <allegro5/keycodes.h>

#include <stdbool.h>
#include <stdio.h>

#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>

#include "allegro5/allegro_primitives.h"
#include "allegro5/keyboard.h"
#include "c_api/io.h"

#include "c_api/input.h"
#include "c_api/texture_manager.h"

typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
} Context;

static Context ctx;

void game_update(lua_State* L, double deltaTime) {
    lua_getglobal(L, "Game");
    lua_getfield(L, -1, "update");
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, deltaTime);
        if (lua_pcall(L, 1, 0, 0)) {
            printf("Erro ao chamar função: %s\n", lua_tostring(L, -1));
        }
    }
}

void game_draw(lua_State* L) {
    lua_getglobal(L, "Game");
    lua_getfield(L, -1, "draw");
    if (lua_isfunction(L, -1)) {
        lua_pcall(L, 0, 0, 0);
    }
}

int main(void) {    
    Context tmp_ctx = {0};
    ctx = tmp_ctx;

    bool running = true;
    int retVal = 0;

    if (!al_init()) {
        fprintf(stderr, "Erro ao inicializar allegro\n");
        retVal = 1;
        goto cleanup;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Erro ao inicializar Allegro Image Addon\n");
        retVal = 1;
        goto cleanup;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Erro ao inicializar Allegro Primitives Addon\n");
        retVal = 1;
        goto cleanup;
    }

    ctx.timer = al_create_timer(1 / 60.0);
    if (!ctx.timer) {
        fprintf(stderr, "Erro ao criar o timer\n");
        retVal = 1;
        goto cleanup;
    }

    ctx.display = al_create_display(800, 600);
    if (!ctx.display) {
        fprintf(stderr, "Erro ao criar display\n");
        retVal = 1;
        goto cleanup;
    }

    ctx.queue = al_create_event_queue();
    if (!ctx.queue) {
        fprintf(stderr, "Erro ai criar event queue\n");
        retVal = 1;
        goto cleanup;
    }

    al_install_keyboard();

    al_register_event_source(ctx.queue, al_get_display_event_source(ctx.display));
    al_register_event_source(ctx.queue, al_get_timer_event_source(ctx.timer));
    al_register_event_source(ctx.queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    File engineLuaFile = parhelia_io_read_file("lua_api/parhelia.lua");

    input_init();
    create_global_texture_manager();
    parhelia_texture_manager_load_error_texture();

    // garantir que não ocorra erros carregando os módulos da engine
    if (luaL_dostring(L, engineLuaFile.data) != LUA_OK) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        return 1;
    }

    lua_setglobal(L, "Parhelia");
    
    // Essa função pode falhar, porque depende do script principal do jogo
    // que o usuário cria, caso a engine não ache esse script, avisa e fecha
    if (luaL_dofile(L, "scripts/game.lua") != LUA_OK) {
        MessageBox(NULL, lua_tostring(L, -1), "Parhelia Engine Error", MB_OK | MB_ICONERROR);
        retVal = 1;
        goto cleanup;
    }
    
    al_start_timer(ctx.timer);
    double lastTime = al_get_time();

    while (running) {
        ALLEGRO_EVENT event;

        if (al_get_next_event(ctx.queue, &event)) {
            switch (event.type) {
                case ALLEGRO_EVENT_KEY_DOWN: {
                    keystate.keys[event.keyboard.keycode] = true;
                } break;

                case ALLEGRO_EVENT_KEY_UP: {
                    keystate.keys[event.keyboard.keycode] = false;
                } break;

                case ALLEGRO_EVENT_TIMER: {
                    double currentTime = al_get_time();
                    double deltaTime = currentTime - lastTime;
                    lastTime = currentTime;
                    // lógica do jogo roda em um intervalo fixo e envia o delta time pra função em Lua
                    game_update(L, deltaTime);
                } break;

                case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                    running = false;
                } break;
                    
                default:
                    break;
            }
        }

        game_draw(L);
    }

cleanup:
    al_destroy_display(ctx.display);
    al_destroy_event_queue(ctx.queue);
    al_destroy_timer(ctx.timer);
    lua_close(L);
    destroy_global_texture_manager();

    return retVal;
}
