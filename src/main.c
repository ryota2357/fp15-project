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

#define LYRICS_RENDERER(number, size, words, duration)                               \
    void lyrics_renderer##number(const Frame* const frame, const uint32_t time) {    \
        if (time > duration) return;                                                 \
        const uint64_t width = frame->width;                                         \
        for (int i = -((size) / 2); i < ((size) + 1) / 2; ++i) {                     \
            int idx = i + (size) / 2;                                                \
            if (words[idx].code == 0) continue;                                      \
            uint16_t x = (width / 2) + (20 * i);                                     \
            draw_char_at(frame, words[idx], 2, x, (BADAPPLE_FRAME_HEIGHT * 4) - 30); \
        }                                                                            \
    }


const Char32 lyrics01[11] = { {.chars = "流"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "く"}, {.code = 0}, {.chars = "時"}, {.chars = "の"}, {.chars = "中"}, {.chars = "で"}, {.chars = "で"}, {.chars = "も"}, };
LYRICS_RENDERER(01, 11, lyrics01, 100)

const Char32 lyrics02[14] = { {.chars = "気"}, {.chars = "だ"}, {.chars = "る"}, {.chars = "さ"}, {.chars = "が"}, {.chars = "ほ"}, {.chars = "ら"}, {.chars = "ぐ"}, {.chars = "ル"}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "廻"}, {.chars = "っ"}, {.chars = "て"}, };
LYRICS_RENDERER(02, 14, lyrics02, 100)

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
    Movie_add_renderer(&movie, lyrics_renderer01, 100);
    Movie_add_renderer(&movie, lyrics_renderer02, 200);

    Movie_build(&movie, build_dir);
    Movie_free(&movie);

    return 0;
}
