/* 
 * This file is part of EasyPG (Easy Password Generator).
 *
 * See LICENSE for licensing information.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <openssl/rand.h>


int gen_random_bytes(uint8_t *buf, size_t in_size) {

    RAND_poll();

    if (RAND_status() != 1) {
        return EXIT_FAILURE;
    }
    if (RAND_bytes(buf, in_size) != 1) {
        return EXIT_FAILURE;
    }

    RAND_cleanup();
    return EXIT_SUCCESS;
}
