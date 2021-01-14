/* 
 * This file is part of EasyPG (Easy Password Generator).
 *
 * See LICENSE for licensing information.
 */

#ifndef MEMORY_H
#define MEMORY_H

#if defined(__GNUC__)
#define memory_barrier() __sync_synchronize()
#else
#define memory_barrier()
#endif

void explicit_memzero(char *buf, size_t n);

#endif /* MEMORY_H */
