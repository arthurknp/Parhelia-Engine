#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* data;
    size_t len;
    bool isValid;
} ParheliaFile;

ParheliaFile parhelia_io_read_file(const char* path);

#endif