@echo off

set files=src/main.c src/c_api/io/io.c src/c_api/renderer/renderer.c src/c_api/input/input.c src/c_api/texture_manager/texture_manager.c

tcc -Wl,-subsystem=console %files% -I include/ -L tcc-defs/ -luser32 -lallegro -lluajit -lallegro_image -lallegro_primitives -lallegro_memfile -o Parhelia.exe