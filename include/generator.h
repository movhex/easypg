/* 
 * This file is part of EasyPG (Easy Password Generator).
 *
 * See LICENSE for licensing information.
 */

#ifndef GENERATOR_H
#define GENERATOR_H

typedef enum {
    FULL_ASCII_MODE,
    SHORT_ASCII_MODE
} generator_mode_t;


int get_random_ascii_string(char *str, size_t in_size, generator_mode_t mode);

#endif /* GENERATOR_H */
