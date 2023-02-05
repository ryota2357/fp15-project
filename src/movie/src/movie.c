#include "../include/movie.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/free.h"

static void ensure_not_freed(const Movie* const movie) {
    if (movie->renderers == NULL) {
        fprintf(stderr, "Movie is freed");
        exit(1);
    }
}

Movie Movie_new(const uint16_t width, const uint16_t height, const uint32_t length) {
    int c = 4;
    return (Movie){
        .height = height,
        .width = width,
        .length = length,
        .renderers = (Renderer*)malloc(sizeof(Renderer) * c),
        .renderer_delay = (uint32_t*)malloc(sizeof(uint32_t) * c),
        .renderer_count = 0,
        .__capacity = c
    };
}

void Movie_add_renderer(Movie* self, Renderer renderer, const uint32_t delay) {
    ensure_not_freed(self);
    const size_t count = self->renderer_count;
    if (count >= self->__capacity) {
        self->__capacity <<= 1;
        const size_t cap = self->__capacity;
        self->renderers = realloc(self->renderers, sizeof(Renderer) * cap);
        self->renderer_delay = realloc(self->renderer_delay, sizeof(uint32_t) * cap);
    }
    self->renderers[count] = renderer;
    self->renderer_delay[count] = delay;
    self->renderer_count += 1;
}

void Movie_build(const Movie* const self, const char* build_dir) {
    ensure_not_freed(self);
    const uint32_t length = self->length;
    const size_t count = self->renderer_count;
    for (uint32_t time = 0; time < length; ++time) {
        Frame frame = Frame_new(self->width, self->height);
        for (size_t i = 0; i < count; ++i) {
            uint32_t delay = self->renderer_delay[i];
            if (delay > time) continue;
            self->renderers[i](&frame, time - delay);
        }
        char* name = calloc(strlen(build_dir) + 10, sizeof(char));  // 10 is "/00000.ppm" length
        sprintf(name, "%s/%05d.ppm", build_dir, time);
        Frame_write_file(&frame, name);
        Frame_free(&frame);
        FREE(name);
    }
}

void Movie_free(Movie* self) {
    FREE(self->renderers);
    FREE(self->renderer_delay);
    self->renderer_count = 0;
    self->__capacity = 0;
}
