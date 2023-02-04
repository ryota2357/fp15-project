#include "../include/bitset128.h"

#include <stdio.h>
#include <stdlib.h>

static const uint64_t ONE = 1;

bool BitSet128_is_1(const BitSet128* const self, const uint8_t bit) {
    if (bit < 64) {
        return (self->bit1 & ONE << bit) != 0;
    } else if (bit < 128) {
        return (self->bit2 & ONE << (bit - 64)) != 0;
    } else {
        fprintf(stderr, "Index out of range error: bit must lower than 128 but %d", bit);
        exit(1);
    }
}

bool BitSet128_is_0(const BitSet128* const self, const uint8_t bit) {
    return !BitSet128_is_1(self, bit);
}

void BitSet128_set_1(BitSet128* self, const uint8_t bit) {
    if (bit < 64) {
        self->bit1 |= (ONE << bit);
    } else if (bit < 128) {
        self->bit2 |= (ONE << (bit - 64));
    } else {
        fprintf(stderr, "Index out of range error: bit must lower than 128 but %d", bit);
        exit(1);
    }
}

void BitSet128_set_0(BitSet128* self, const uint8_t bit) {
    if (bit < 64) {
        self->bit1 |= (ONE << bit);
        self->bit1 ^= (ONE << bit);
    } else if (bit < 128) {
        self->bit2 |= (ONE << (bit - 64));
        self->bit2 ^= (ONE << (bit - 64));
    } else {
        fprintf(stderr, "Index out of range error: bit must lower than 128 but %d", bit);
        exit(1);
    }
}
