/* 
 * This file is part of EasyPG (Easy Password Generator).
 *
 * See LICENSE for licensing information.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "random.h"
#include "generator.h"


static char symbols[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'S',
    'R', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
    'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 's', 'r', 'u',
    'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4',
    '5', '6', '7', '8', '9', '0', '!', '~', '@',
    '#', '$', '%', '<', '>', ';', '^', '&', '*',
    '(', ')', '-', '+', '=', '_', '?', '|', '/'
};


int get_random_ascii_string(char *str, size_t in_size, generator_mode_t mode) {

    uint8_t buffer[in_size];
    uint8_t boundary;
    uint8_t index;

    switch (mode) {
        case FULL_ASCII_MODE:
            boundary = sizeof(symbols);
            break;
        case SHORT_ASCII_MODE:
            boundary = sizeof(symbols) - 21;
            break;
        default:
            return EXIT_FAILURE;
    } 

    if (gen_random_bytes(buffer, in_size) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < in_size; ++i) {
        index = buffer[i];
        /* Convert random number for interval */
        index %= boundary;
        str[i] = symbols[index];
        if ((i + 1) == in_size) {
            str[(i + 1)] = '\0';
        }
    }
    return EXIT_SUCCESS;
}
