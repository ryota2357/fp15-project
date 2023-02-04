#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FREE(x)     \
    do {            \
        free(x);    \
        (x) = NULL; \
    } while (0)
