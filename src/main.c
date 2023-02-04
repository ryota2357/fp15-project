#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "frame.h"
#include "movie.h"

void sample_renderer(const Frame* const frame, const uint32_t time) {
    Color color;
    double pos_x, pos_y, r;
    if (time < 100) {
        color = color_new(0, 255, 0);
        pos_x = 50 + time;
        pos_y = 100;
        r = 20;
    } else {
        color = color_new(255, 0, 0);
        pos_x = 150;
        pos_y = 100 - (time - 100);
        r = 20 - (time - 100.0) / 5;
    }
    for (uint16_t x = 0; x < frame->width; ++x) {
        for (uint16_t y = 0; y < frame->height; ++y) {
            double x2 = (x - pos_x) * (x - pos_x);
            double y2 = (y - pos_y) * (y - pos_y);
            if (x2 + y2 > r * r) continue;
            Frame_draw(frame, x, y, color);
        }
    }
}

int main(int argc, char* args[]) {
    if (argc != 2) {
        fprintf(stderr, "Argument Error, the number of argument must be 2 but %d\n", argc);
        exit(1);
    }
    char* build_dir = args[1];

    Movie movie = Movie_new(300, 200, 200);

    Movie_add_renderer(&movie, sample_renderer, 0);

    Movie_build(&movie, build_dir);
    Movie_free(&movie);

    return 0;
}
