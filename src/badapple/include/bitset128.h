#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint64_t bit1;
    uint64_t bit2;
} BitSet128;

bool BitSet128_is_1(const BitSet128* const self, const uint8_t bit);

bool BitSet128_is_0(const BitSet128* const self, const uint8_t bit);

void BitSet128_set_1(BitSet128* self, const uint8_t bit);

void BitSet128_set_0(BitSet128* self, const uint8_t bit);
