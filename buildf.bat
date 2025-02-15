set files=src/parhelia.c src/c-api/io/io.c

tcc -Wl,-subsystem=console %files% -I include/ -L tcc-defs/ -luser32 -lallegro -lluajit -lallegro_image -o Parhelia.exe