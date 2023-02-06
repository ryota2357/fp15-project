#include "../include/movie.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/free.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

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

static void build_for_time(const Movie* const movie, const char* filename, const uint32_t time) {
    ensure_not_freed(movie);
    const size_t count = movie->renderer_count;
    Frame frame = Frame_new(movie->width, movie->height);
    for (size_t i = 0; i < count; ++i) {
        uint32_t delay = movie->renderer_delay[i];
        if (delay > time) continue;
        movie->renderers[i](&frame, time - delay);
    }

    Frame_write_file(&frame, filename);
    Frame_free(&frame);
}

static void show_progress_in_current_line(const uint32_t time, const uint32_t length) {
    printf("\033[2K");
    printf("    %d / %d\n", time, length);
    printf("\033[1F");
    fflush(stdout);
}

void Movie_build(const Movie* const self, const char* build_dir) {
    ensure_not_freed(self);
    const uint32_t length = self->length;
    for (uint32_t time = 0; time < length; ++time) {
        char* name = calloc(strlen(build_dir) + 15, sizeof(char));  // 15 is greater than "/0000.ppm" length
        sprintf(name, "%s/%04d.ppm", build_dir, time);
        build_for_time(self, name, time);
        FREE(name);
        show_progress_in_current_line(time, length);
    }
}

void Movie_debug_build(const Movie* const self, const char* build_dir, const uint32_t start_time, const uint32_t end_time) {
    ensure_not_freed(self);
    if (start_time >= end_time) {
        fprintf(stderr, "Argument error: start_time (%d) is later than end_time (%d)", start_time, end_time);
        exit(1);
    }
    const uint32_t length = min(self->length, end_time);
    for (uint32_t time = start_time; time < length; ++time) {
        char* name = calloc(strlen(build_dir) + 15, sizeof(char));   // 15 is greater than "/0000.ppm" length
        sprintf(name, "%s/%04d.ppm", build_dir, time - start_time);  // file name must starts 0000.ppm because of ffmpeg.
        build_for_time(self, name, time);
        FREE(name);
        show_progress_in_current_line(time - start_time, length - start_time);
    }
}

void Movie_free(Movie* self) {
    FREE(self->renderers);
    FREE(self->renderer_delay);
    self->renderer_count = 0;
    self->__capacity = 0;
}
