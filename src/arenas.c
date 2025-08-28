#include "arenas.h"

void ArenaInit(Arena *arena, uint64_t buffer_size) {
    *arena = (Arena){
        .buffer = malloc(buffer_size),
        .offset = 0,
        .buffer_size = buffer_size,
    };
}

void *ArenaAlloc(Arena *arena, uint64_t nbr_elements, uint64_t size_element, uint64_t alignment) {
    if (!ValidAlignment(alignment)) return NULL;

    uintptr_t alloc_size = nbr_elements * size_element;
    if (alloc_size < size_element) return NULL;

    uintptr_t total_offset = (uintptr_t)arena->offset + (uintptr_t)arena->buffer;
    uintptr_t padding = (~total_offset+1) & (alignment-1);
    total_offset += padding;

    if (ArenaOverflow(arena, alloc_size)) return NULL;  
    
    arena->offset += (padding + alloc_size);
    memset((void*)total_offset, 0, alloc_size);
    return (void*)total_offset;
}

void ArenaReset(Arena *arena) {
    if (arena) {
        arena->offset = 0;
        memset(arena->buffer, 0, arena->buffer_size);
    }
}

void ArenaFree(Arena *arena) {
    if (arena && arena->buffer) {
        free(arena->buffer);
        arena->buffer = NULL;
        arena->offset = 0;
        arena->buffer_size = 0;
    }
}

#include <stdio.h>
int main() {
    Arena arena;
    ArenaInit(&arena, KB(1));
    ArenaAlloc(&arena, 42, sizeof(int), sizeof(int));
    ArenaReset(&arena);
    char *str = ArenaAlloc(&arena, 16, sizeof(char), sizeof(char));
    str = "Hello, world!";
    printf("%s\n", str);
    ArenaFree(&arena);
    return (0);
}