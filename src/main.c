/* 
 * This file is part of EasyPG (Easy Password Generator).
 *
 * See LICENSE for licensing information.
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <openssl/crypto.h>

#include "generator.h"
#include "memory.h"
#include "version.h"

#define MAX_PASSWDLEN  10000

static bool show_help;
static bool show_version;
static bool without_spec;
static ssize_t result_len;


static int parse_argv(int argc, char *const *argv) {

    char *ptr, c;

    while ((c = getopt(argc, argv, ":s:vh")) != -1) {

        switch (c) {
        case 'h':
            show_help = true;
            break;
        case 'v':
            show_version = true;
            break;
        case 's':
            without_spec = true;
            result_len = atol(optarg);
            break;
        /* 
         * TODO:
         * case ':':
         *     break;
         */
        case '?':
            optind -= 1;
            goto failed;
        }
    }

    if (optind == 1 && argc == 2) {

        for (ptr = argv[optind]; *ptr; ++ptr) {
            if (!isdigit(*ptr)) {
                goto failed;
            }
        }

        result_len = atol(argv[optind]);
    }

    return 0;

failed:
    return optind;
}

static void show_version_info(void) {
    fprintf(stdout, "easypg %s %s\n\n",
        EASYPG_VERSION_STR, EASYPG_VERSION_DATE);
    fprintf(stdout, "Using %s\n",
        SSLeay_version(SSLEAY_VERSION));
}

static void show_help_info(void) {
    fprintf(stdout,
        "Usage: easypg [options...] LENGTH\n"
        "Example: easypg 32 \n"
        "LENGTH can be only positive number\n\n"
        "Options:\n"
        "  -h                             Displays this message.\n"
        "  -v                             Displays version information.\n"
        "  -s                             Suppress using special characters.\n"
    );
}

int main(int argc, char *const argv[]) {

    static char buf[MAX_PASSWDLEN];
    int rv, err;

    rv = parse_argv(argc, argv);
    if (rv) {
        fprintf(stderr, "easypg: invalid option -- \"%s\"\n", argv[rv]);
        show_help_info();
        return 1;
    }

    if (show_version) {
        show_version_info();
        return 0;
    }

    if (show_help) {
        show_help_info();
        return 0;
    }

    if (!result_len) {
        fprintf(stderr, "You need to specify password length\n");
        return 1;
    }
    else if (result_len < 0) {
        fprintf(stderr, "Password length must be positive number\n");
        return 1;
    }
    else if (result_len > MAX_PASSWDLEN) {
        fprintf(stderr, "Length of password is too big.\n");
        return 1;
    }

    if (without_spec) {
        err = get_random_ascii_string(buf, result_len, SHORT_ASCII_MODE);
    }
    else {
        err = get_random_ascii_string(buf, result_len, FULL_ASCII_MODE);
    }

    if (err != EXIT_SUCCESS) {
        fprintf(stderr, "Failed to generate random bytes.\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "%s\n", buf);

    explicit_memzero(buf, result_len);

    return EXIT_SUCCESS;
}
