#include "../io.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define IO_READ_CHUNK_SIZE 2097152
#define IO_READ_ERROR_GENERAL "Erro lendo arquivo: %s. Errno: %d\n"
#define IO_READ_ERROR_MEMORY "Memória insuficiente para ler arquivo: %s\n"

File parhelia_io_read_file(const char* path) {
    File file = {.isValid = false};

    FILE* fileHandle = fopen(path, "rb");
    if (!fileHandle || ferror(fileHandle)) {
        fprintf(stderr, IO_READ_ERROR_GENERAL, path, errno);
        return file;
    }

    char* data = NULL;
    char* tmp;
    size_t used = 0;
    size_t size = 0;
    size_t n;

    while (true) {
        if (used + IO_READ_CHUNK_SIZE + 1 > size) {
            size = used + IO_READ_CHUNK_SIZE + 1;

            if (size <= used) {
                free(data);
                fprintf(stderr, "Arquivo muito grande: %s\n", path);
                return file;
            }

            tmp = realloc(data, size);
            if (!tmp) {
                free(data);
                fprintf(stderr, IO_READ_ERROR_MEMORY, path);
                return file;
            }

            data = tmp;
        }

        n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fileHandle);
        if (n == 0) {
            break;
        }

        used += n;
    }

    if (ferror(fileHandle)) {
        free(data);
        fprintf(stderr, IO_READ_ERROR_GENERAL, path, errno);
        return file;
    }

    tmp = realloc(data, used + 1);
    if (!tmp) {
        free(data);
        fprintf(stderr, IO_READ_ERROR_MEMORY, path);
        return file;
    }

    data = tmp;
    data[used] = 0;

    file.data = data;
    file.len = used;
    file.isValid = true;

    return file;

}
