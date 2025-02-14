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

#include <stdbool.h>
#include <stdio.h>

#include "io.h"

#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>

typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
} Context;

static Context ctx;

void game_load_content(lua_State* L) {
    lua_getglobal(L, "Game");
    lua_getfield(L, -1, "load_content");
    if (lua_isfunction(L, -1)) {
        lua_pcall(L, 0, 0, 0);
    }
}

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

    if (!al_init()) {
        fprintf(stderr, "Erro ao inicializar allegro\n");
        return 1;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Erro ao inicializar Allegro Image Addon\n");
        return 1;
    }

    ctx.timer = al_create_timer(1 / 60.0);
    if (!ctx.timer) {
        fprintf(stderr, "Erro ao criar o timer\n");
        return 1;
    }

    ctx.display = al_create_display(800, 600);
    if (!ctx.display) {
        fprintf(stderr, "Erro ao criar display\n");
        return 1;
    }

    ctx.queue = al_create_event_queue();
    if (!ctx.queue) {
        fprintf(stderr, "Erro ai criar event queue\n");
        return 1;
    }

    al_register_event_source(ctx.queue, al_get_display_event_source(ctx.display));
    al_register_event_source(ctx.queue, al_get_timer_event_source(ctx.timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    ParheliaFile engineLuaFile = parhelia_io_read_file("wrapper/parhelia.lua");

    // garantir que não ocorra erros carregando os módulos da engine
    assert(luaL_dostring(L, engineLuaFile.data) == LUA_OK); 

    lua_setglobal(L, "Parhelia");
    
    // Essa função pode falhar, porque depende do script principal do jogo
    // que o usuário cria, caso a engine não ache esse script, avisa e fecha
    if (luaL_dofile(L, "scripts/game.lua") != LUA_OK) {
        MessageBox(NULL, lua_tostring(L, -1), "Parhelia Engine Error", MB_OK | MB_ICONERROR);
        al_destroy_display(ctx.display);
        al_destroy_event_queue(ctx.queue);
        lua_close(L);
        return 1;
    }

    // rodando funções definidas em Lua já
    game_load_content(L);

    al_start_timer(ctx.timer);
    double lastTime = al_get_time();

    // textura de teste
    ALLEGRO_BITMAP* teste_textura = al_load_bitmap("teste.bmp");
    assert(teste_textura != NULL);

    while (running) {
        ALLEGRO_EVENT event;

        if (al_get_next_event(ctx.queue, &event)) {
            switch (event.type) {
                case ALLEGRO_EVENT_TIMER: {
                    double currentTime = al_get_time();
                    double deltaTime = currentTime - lastTime;
                    lastTime = currentTime;
                    game_update(L, deltaTime);
                } break;

                case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                    running = false;
                } break;
                    
                default: {
                    fprintf(stderr, "Tipo de evento não suportado: %d\n", event.type);
                } break;
            }
        }

        al_clear_to_color(al_map_rgb(255, 255, 255));
        game_draw(L);
        al_draw_bitmap(teste_textura, 0.0f, 0.0f, 0);
        al_flip_display();
    }

	al_destroy_display(ctx.display);
	al_destroy_event_queue(ctx.queue);
    al_destroy_bitmap(teste_textura);
    lua_close(L);
    return 0;
}
