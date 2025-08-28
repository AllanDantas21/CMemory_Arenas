#ifndef ARENAS_H
#define ARENAS_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structs.h"

#define KB(x) (x * 1024)

bool ValidAlignment(uint64_t alignment);
bool ArenaOverflow(Arena *arena, uint64_t alloc_size);

#endif