#pragma once

#include <stddef.h>
#include <stdint.h>
#include "renderer.h"

typedef struct {
    const uint16_t width;
    const uint16_t height;
    const uint32_t length;
    Renderer* renderers;
    size_t renderer_count;
    uint32_t* renderer_delay;
    size_t __capacity;
} Movie;

Movie Movie_new(const uint16_t width, const uint16_t height, const uint32_t length);

void Movie_add_renderer(Movie* self, Renderer renderer, const uint32_t delay);

void Movie_build(const Movie* const self, const char* build_dir);

void Movie_debug_build(const Movie* const self, const char* build_dir, const uint32_t start_time, const uint32_t end_time);

void Movie_free(Movie* self);
