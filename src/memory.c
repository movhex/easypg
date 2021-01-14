/* 
 * This file is part of EasyPG (Easy Password Generator).
 *
 * See LICENSE for licensing information.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "memory.h"


void explicit_memzero(char *buf, size_t n) {
    memset(buf, 0, n);
    memory_barrier();
}
