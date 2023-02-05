#include "../include/frame.h"

static void ensure_not_freed(const Frame* const frame) {
    if (frame->pixels == NULL) {
        fprintf(stderr, "Frame is freed");
        exit(1);
    }
}

static uint32_t calc_pos(const Frame* const frame, const uint16_t x, const uint16_t y) {
    if (x < frame->width && y < frame->height) {
        return ((uint32_t)y) * frame->width + x;
    }
    fprintf(stderr, "Index out of range: (%d, %d), max is (%d, %d)", x, y, frame->width, frame->height);
    exit(1);
}

Frame Frame_new(const uint16_t width, const uint16_t height) {
    const uint32_t size = ((int32_t)(width)) * height;
    Color* p = malloc(sizeof(Color) * size);
    for (uint32_t i = 0; i < size; ++i) {
        p[i] = color_new(255, 255, 255);
    }
    return (Frame){
        .width = width,
        .height = height,
        .pixels = p
    };
}

Color Frame_at(const Frame* const self, const uint16_t x, const uint16_t y) {
    return self->pixels[calc_pos(self, x, y)];
}

void Frame_draw(const Frame* const self, const uint16_t x, const uint16_t y, const Color color) {
    ensure_not_freed(self);
    if (x < self->width && y < self->height) {
        self->pixels[calc_pos(self, x, y)] = color;
    }
}

void Frame_write_file(const Frame* const self, const char* filename) {
    ensure_not_freed(self);
    FILE* file = fopen(filename, "wb");
    const uint16_t width = self->width;
    const uint16_t height = self->height;
    const Color* pixels = self->pixels;
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    for (uint16_t y = 0; y < height; ++y) {
        for (uint16_t x = 0; x < width; ++x) {
            const Color c = pixels[calc_pos(self, x, y)];
            fprintf(file, "%c%c%c", c.r, c.g, c.b);
        }
    }
    fclose(file);
}

void Frame_free(Frame* self) {
    FREE(self->pixels);
}
