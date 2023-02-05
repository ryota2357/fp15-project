#pragma once

#define FREE(x)     \
    do {            \
        free(x);    \
        (x) = NULL; \
    } while (0)
