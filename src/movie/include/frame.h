#pragma once

#include "color.h"
#include "common.h"

typedef struct {
    const uint16_t width;
    const uint16_t height;
    Color* pixels;
} Frame;

Frame Frame_new(const uint16_t width, const uint16_t height);

Color Frame_at(const Frame* const self, const uint16_t x, const uint16_t y);

void Frame_draw(const Frame* const self, const uint16_t x, const uint16_t y, const Color color);

void Frame_write_file(const Frame* const self, const char* filename);

void Frame_free(Frame* frame);
