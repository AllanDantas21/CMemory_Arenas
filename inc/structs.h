#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

typedef struct {
    char *buffer;
    uint64_t offset;
    uint64_t buffer_size;
} Arena;

#endif