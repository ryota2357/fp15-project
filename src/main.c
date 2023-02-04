#include <stdio.h>
#include <stdlib.h>
#include "badapple.h"
#include "bitset128.h"
#include "color.h"
#include "frame.h"
#include "movie.h"

// 適当なアルゴで解像度上げた方がいい。(https://qiita.com/yoya/items/f167b2598fec98679422)
void badapple_render(const Frame* const frame, const uint32_t time) {
    BadAppleFrame apple = badapple_get(time);
    for (uint16_t x = 0; x < BADAPPLE_FRAME_WIDTH; ++x) {
        for (uint16_t y = 0; y < BADAPPLE_FRAME_HEIGHT; ++y) {
            if (BitSet128_is_1(&apple.lines[y], x)) {
                continue;
            }
            for (int i = 0; i < 4; ++i) {
                Frame_draw(frame, 4 * x + i, 4 * y + 0, color_new(0, 0, 0));
                Frame_draw(frame, 4 * x + i, 4 * y + 1, color_new(0, 0, 0));
                Frame_draw(frame, 4 * x + i, 4 * y + 2, color_new(0, 0, 0));
                Frame_draw(frame, 4 * x + i, 4 * y + 3, color_new(0, 0, 0));
            }
        }
    }
}

int main(int argc, char* args[]) {
    if (argc != 2) {
        fprintf(stderr, "Argument Error, the number of argument must be 2 but %d\n", argc);
        exit(1);
    }
    char* build_dir = args[1];

    badapple_init();

    Movie movie = Movie_new(BADAPPLE_FRAME_WIDTH * 4, BADAPPLE_FRAME_HEIGHT * 4, BADAPPLE_FRAME_COUNT);

    Movie_add_renderer(&movie, badapple_render, 0);

    Movie_build(&movie, build_dir);
    Movie_free(&movie);

    return 0;
}
