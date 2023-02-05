#pragma once

#include <stdint.h>

#define TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE (40)

typedef union {
    char chars[4];
    uint32_t code;
} Char32;

typedef struct {
    uint64_t bitmap[TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE];
    Char32 character;
} CharBitMap;

void font_bitmap_init(void);

CharBitMap font_bitmap_get(const Char32 chars);
