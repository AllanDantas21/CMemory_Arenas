#include "arenas.h"

bool ValidAlignment(uint64_t alignment) {
    return ((alignment == 0) || (alignment & (alignment - 1)) == 1);
}

bool ArenaOverflow(Arena *arena, uint64_t alloc_size) {
    return (arena->offset + alloc_size > arena->buffer_size);
}