#pragma once

#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

Color color_new(const uint8_t r, const uint8_t g, const uint8_t b);
