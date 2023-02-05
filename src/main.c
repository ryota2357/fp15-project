#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "badapple.h"
#include "bitset128.h"
#include "color.h"
#include "font_bitmap.h"
#include "frame.h"
#include "movie.h"

// 適当なアルゴで解像度上げた方がいい。(https://qiita.com/yoya/items/f167b2598fec98679422)
void badapple_renderer(const Frame* const frame, const uint32_t time) {
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

void draw_char_at(const Frame* const frame, const Char32 ch, const uint8_t rate, const uint16_t posx, const uint16_t posy) {
    CharBitMap map = font_bitmap_get(ch);
    for (uint16_t y = 0; y < (40 / rate); ++y) {
        for (uint16_t x = 0; x < (40 / rate); ++x) {
            uint16_t v = 0;
            for (int i = 0; i < rate; ++i) for (int j = 0; j < rate; ++j) {
                v += (map.bitmap[rate * y + i] & (1ll << (rate * x + j)) ? 1 : 0);
            }
            if (v <= (rate * rate / 2)) {
                continue;
            }
            Color frame_color = Frame_at(frame, posx + x, posy + y);
            uint32_t ave = ((uint32_t)frame_color.r + frame_color.g + frame_color.b) / 3;
            Frame_draw(frame, posx + x, posy + y, ave > 100 ? color_new(0, 0, 0) : color_new(255, 255, 255));
        }
    }
}

// 5 4 3 2 1 0 1 2 3 4 5
// 流れてく　時の中ででも
void lyrics1_renderer(const Frame* const frame, const uint32_t time) {
    static const Char32 words[10] = {
        {.chars = "流"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "く"},
        {.chars = "時"}, {.chars = "の"}, {.chars = "中"}, {.chars = "で"}, {.chars = "で"}, {.chars = "も"},
    };
    const uint16_t width = frame->width;
    const uint16_t y = (BADAPPLE_FRAME_HEIGHT * 4) - 30;
    for (int i = 5; i >= 2; --i) {
        uint16_t x = (width / 2) - (20 * i);
        draw_char_at(frame, words[5 - i], 2, x, y);
    }
    for (int i = 0; i <= 5; ++i) {
        uint16_t x = (width / 2) + (20 * i);
        draw_char_at(frame, words[4 + i], 2, x, y);
    }
}

int main(int argc, char* args[]) {
    if (argc != 2) {
        fprintf(stderr, "Argument Error, the number of argument must be 2 but %d\n", argc);
        exit(1);
    }
    char* build_dir = args[1];

    font_bitmap_init();
    badapple_init();

    Movie movie = Movie_new(BADAPPLE_FRAME_WIDTH * 4, BADAPPLE_FRAME_HEIGHT * 4, 1000);

    Movie_add_renderer(&movie, badapple_renderer, 0);
    Movie_add_renderer(&movie, lyrics1_renderer, 100);

    Movie_build(&movie, build_dir);
    Movie_free(&movie);

    return 0;
}
