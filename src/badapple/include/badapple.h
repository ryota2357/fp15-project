#pragma once

#include <stdint.h>
#include "bitset128.h"

#define BADAPPLE_FRAME_COUNT (6572)
#define BADAPPLE_FRAME_HEIGHT (4 * 18)
#define BADAPPLE_FRAME_WIDTH (2 * 48)

typedef struct {
    BitSet128 lines[BADAPPLE_FRAME_HEIGHT];
    uint32_t start_time;  // ms
    uint32_t end_time;    // ms
} BadAppleFrame;

void badapple_init(void);

BadAppleFrame badapple_get(const uint32_t count);
