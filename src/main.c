#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "badapple.h"
#include "bitset128.h"
#include "color.h"
#include "font_bitmap.h"
#include "frame.h"
#include "movie.h"

#define LYRICS_RENDERER_PROTOTYPE_DEFINITION(number) void lyrics_renderer##number(const Frame* const frame, const uint32_t time);
#define LYRICS_RENDERER(number, words, duration)                                     \
    void lyrics_renderer##number(const Frame* const frame, const uint32_t time) {    \
        if (time > duration) return;                                                 \
        const uint16_t size = sizeof(words) / sizeof(words[0]);                      \
        const uint16_t width = frame->width;                                         \
        for (int i = -(size / 2); i < (size + 1) / 2; ++i) {                         \
            int idx = i + (size / 2);                                                \
            if (words[idx].code == 0) continue;                                      \
            uint16_t x = (width / 2) + (20 * i);                                     \
            draw_char_at(frame, words[idx], 2, x, (BADAPPLE_FRAME_HEIGHT * 4) - 30); \
        }                                                                            \
    }

LYRICS_RENDERER_PROTOTYPE_DEFINITION(01) LYRICS_RENDERER_PROTOTYPE_DEFINITION(02) LYRICS_RENDERER_PROTOTYPE_DEFINITION(03) LYRICS_RENDERER_PROTOTYPE_DEFINITION(04) LYRICS_RENDERER_PROTOTYPE_DEFINITION(05) LYRICS_RENDERER_PROTOTYPE_DEFINITION(06) LYRICS_RENDERER_PROTOTYPE_DEFINITION(07) LYRICS_RENDERER_PROTOTYPE_DEFINITION(08) LYRICS_RENDERER_PROTOTYPE_DEFINITION(09) LYRICS_RENDERER_PROTOTYPE_DEFINITION(10)
LYRICS_RENDERER_PROTOTYPE_DEFINITION(11) LYRICS_RENDERER_PROTOTYPE_DEFINITION(12) LYRICS_RENDERER_PROTOTYPE_DEFINITION(13) LYRICS_RENDERER_PROTOTYPE_DEFINITION(14) LYRICS_RENDERER_PROTOTYPE_DEFINITION(15) LYRICS_RENDERER_PROTOTYPE_DEFINITION(16) LYRICS_RENDERER_PROTOTYPE_DEFINITION(17) LYRICS_RENDERER_PROTOTYPE_DEFINITION(18) LYRICS_RENDERER_PROTOTYPE_DEFINITION(19) LYRICS_RENDERER_PROTOTYPE_DEFINITION(20)
LYRICS_RENDERER_PROTOTYPE_DEFINITION(21) LYRICS_RENDERER_PROTOTYPE_DEFINITION(22) LYRICS_RENDERER_PROTOTYPE_DEFINITION(23) LYRICS_RENDERER_PROTOTYPE_DEFINITION(24) LYRICS_RENDERER_PROTOTYPE_DEFINITION(25) LYRICS_RENDERER_PROTOTYPE_DEFINITION(26) LYRICS_RENDERER_PROTOTYPE_DEFINITION(27) LYRICS_RENDERER_PROTOTYPE_DEFINITION(28) LYRICS_RENDERER_PROTOTYPE_DEFINITION(29) LYRICS_RENDERER_PROTOTYPE_DEFINITION(30)
LYRICS_RENDERER_PROTOTYPE_DEFINITION(31) LYRICS_RENDERER_PROTOTYPE_DEFINITION(32) LYRICS_RENDERER_PROTOTYPE_DEFINITION(33) LYRICS_RENDERER_PROTOTYPE_DEFINITION(34) LYRICS_RENDERER_PROTOTYPE_DEFINITION(35) LYRICS_RENDERER_PROTOTYPE_DEFINITION(36) LYRICS_RENDERER_PROTOTYPE_DEFINITION(37) LYRICS_RENDERER_PROTOTYPE_DEFINITION(38) LYRICS_RENDERER_PROTOTYPE_DEFINITION(39) LYRICS_RENDERER_PROTOTYPE_DEFINITION(40)
LYRICS_RENDERER_PROTOTYPE_DEFINITION(41) LYRICS_RENDERER_PROTOTYPE_DEFINITION(42) LYRICS_RENDERER_PROTOTYPE_DEFINITION(43) LYRICS_RENDERER_PROTOTYPE_DEFINITION(44) LYRICS_RENDERER_PROTOTYPE_DEFINITION(45) LYRICS_RENDERER_PROTOTYPE_DEFINITION(46) LYRICS_RENDERER_PROTOTYPE_DEFINITION(47) LYRICS_RENDERER_PROTOTYPE_DEFINITION(48)

void badapple_renderer(const Frame* const frame, const uint32_t time);

void draw_char_at(const Frame* const frame, const Char32 ch, const uint8_t rate, const uint16_t posx, const uint16_t posy);

int main(int argc, char* args[]) {
    if (argc != 2) {
        fprintf(stderr, "Argument Error, the number of argument must be 2 but %d\n", argc);
        exit(1);
    }
    char* build_dir = args[1];

    font_bitmap_init();
    badapple_init();

    Movie movie = Movie_new(BADAPPLE_FRAME_WIDTH * 4, BADAPPLE_FRAME_HEIGHT * 4, 5000);

    Movie_add_renderer(&movie, badapple_renderer, 0);
    Movie_add_renderer(&movie, lyrics_renderer01, 100);
    Movie_add_renderer(&movie, lyrics_renderer02, 200);
    Movie_add_renderer(&movie, lyrics_renderer03, 300);
    Movie_add_renderer(&movie, lyrics_renderer04, 400);
    Movie_add_renderer(&movie, lyrics_renderer05, 500);
    Movie_add_renderer(&movie, lyrics_renderer06, 600);
    Movie_add_renderer(&movie, lyrics_renderer07, 700);
    Movie_add_renderer(&movie, lyrics_renderer08, 800);
    Movie_add_renderer(&movie, lyrics_renderer09, 900);
    Movie_add_renderer(&movie, lyrics_renderer10, 1000);
    Movie_add_renderer(&movie, lyrics_renderer11, 1100);
    Movie_add_renderer(&movie, lyrics_renderer12, 1200);
    Movie_add_renderer(&movie, lyrics_renderer13, 1300);
    Movie_add_renderer(&movie, lyrics_renderer14, 1400);
    Movie_add_renderer(&movie, lyrics_renderer15, 1500);
    Movie_add_renderer(&movie, lyrics_renderer16, 1600);
    Movie_add_renderer(&movie, lyrics_renderer17, 1700);
    Movie_add_renderer(&movie, lyrics_renderer18, 1800);
    Movie_add_renderer(&movie, lyrics_renderer19, 1900);
    Movie_add_renderer(&movie, lyrics_renderer20, 2000);
    Movie_add_renderer(&movie, lyrics_renderer21, 2100);
    Movie_add_renderer(&movie, lyrics_renderer22, 2200);
    Movie_add_renderer(&movie, lyrics_renderer23, 2300);
    Movie_add_renderer(&movie, lyrics_renderer24, 2400);
    Movie_add_renderer(&movie, lyrics_renderer25, 2500);
    Movie_add_renderer(&movie, lyrics_renderer26, 2600);
    Movie_add_renderer(&movie, lyrics_renderer27, 2700);
    Movie_add_renderer(&movie, lyrics_renderer28, 2800);
    Movie_add_renderer(&movie, lyrics_renderer29, 2900);
    Movie_add_renderer(&movie, lyrics_renderer30, 3000);
    Movie_add_renderer(&movie, lyrics_renderer31, 3100);
    Movie_add_renderer(&movie, lyrics_renderer32, 3200);
    Movie_add_renderer(&movie, lyrics_renderer33, 3300);
    Movie_add_renderer(&movie, lyrics_renderer34, 3400);
    Movie_add_renderer(&movie, lyrics_renderer35, 3500);
    Movie_add_renderer(&movie, lyrics_renderer36, 3600);
    Movie_add_renderer(&movie, lyrics_renderer37, 3700);
    Movie_add_renderer(&movie, lyrics_renderer38, 3800);
    Movie_add_renderer(&movie, lyrics_renderer39, 3900);
    Movie_add_renderer(&movie, lyrics_renderer40, 4000);
    Movie_add_renderer(&movie, lyrics_renderer41, 4100);
    Movie_add_renderer(&movie, lyrics_renderer42, 4200);
    Movie_add_renderer(&movie, lyrics_renderer43, 4300);
    Movie_add_renderer(&movie, lyrics_renderer44, 4400);
    Movie_add_renderer(&movie, lyrics_renderer45, 4500);
    Movie_add_renderer(&movie, lyrics_renderer46, 4600);
    Movie_add_renderer(&movie, lyrics_renderer47, 4700);
    Movie_add_renderer(&movie, lyrics_renderer48, 4800);

    Movie_build(&movie, build_dir);
    Movie_free(&movie);

    return 0;
}

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

const Char32 lyrics01[11] = { {.chars = "流"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "く"}, {.code = 0}, {.chars = "時"}, {.chars = "の"}, {.chars = "中"}, {.chars = "で"}, {.chars = "で"}, {.chars = "も"}, };
LYRICS_RENDERER(01, lyrics01, 100)

const Char32 lyrics02[14] = { {.chars = "気"}, {.chars = "だ"}, {.chars = "る"}, {.chars = "さ"}, {.chars = "が"}, {.chars = "ほ"}, {.chars = "ら"}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "廻"}, {.chars = "っ"}, {.chars = "て"}, };
LYRICS_RENDERER(02, lyrics02, 100)

const Char32 lyrics03[13] = { {.chars = "私"}, {.chars = "か"}, {.chars = "ら"}, {.chars = "離"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "心"}, {.chars = "も"}, {.chars = "見"}, {.chars = "え"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, };
LYRICS_RENDERER(03, lyrics03, 100)

const Char32 lyrics04[6] = { {.chars = "そ"}, {.chars = "う"}, {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, };
LYRICS_RENDERER(04, lyrics04, 100)

const Char32 lyrics05[12] = { {.chars = "自"}, {.chars = "分"}, {.chars = "か"}, {.chars = "ら"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.chars = "な"}, {.chars = "く"}, };
LYRICS_RENDERER(05, lyrics05, 100)

const Char32 lyrics06[12] = { {.chars = "時"}, {.chars = "の"}, {.chars = "隙"}, {.chars = "間"}, {.chars = "に"}, {.code = 0}, {.chars = "流"}, {.chars = "さ"}, {.chars = "れ"}, {.chars = "続"}, {.chars = "け"}, {.chars = "て"}, };
LYRICS_RENDERER(06, lyrics06, 100)

const Char32 lyrics07[13] = { {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, {.code = 0}, {.chars = "周"}, {.chars = "り"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "な"}, {.chars = "ど"}, };
LYRICS_RENDERER(07, lyrics07, 100)

const Char32 lyrics08[7] = { {.chars = "私"}, {.chars = "は"}, {.chars = "私"}, {.chars = "そ"}, {.chars = "れ"}, {.chars = "だ"}, {.chars = "け"}, };
LYRICS_RENDERER(08, lyrics08, 100)

const Char32 lyrics09[13] = { {.chars = "夢"}, {.chars = "見"}, {.chars = "て"}, {.chars = "る"}, {.chars = "？"}, {.code = 0}, {.chars = "何"}, {.chars = "も"}, {.chars = "見"}, {.chars = "て"}, {.chars = "な"}, {.chars = "い"}, {.chars = "？"}, };
LYRICS_RENDERER(09, lyrics09, 100)

const Char32 lyrics10[12] = { {.chars = "語"}, {.chars = "る"}, {.chars = "も"}, {.chars = "無"}, {.chars = "駄"}, {.chars = "な"}, {.code = 0}, {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "言"}, {.chars = "葉"}, };
LYRICS_RENDERER(10, lyrics10, 100)

const Char32 lyrics11[13] = { {.chars = "悲"}, {.chars = "し"}, {.chars = "む"}, {.chars = "な"}, {.chars = "ん"}, {.chars = "て"}, {.code = 0}, {.chars = "疲"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "だ"}, {.chars = "け"}, {.chars = "よ"}, };
LYRICS_RENDERER(11, lyrics11, 100)

const Char32 lyrics12[13] = { {.chars = "何"}, {.chars = "も"}, {.chars = "感"}, {.chars = "じ"}, {.chars = "ず"}, {.code = 0}, {.chars = "過"}, {.chars = "ご"}, {.chars = "せ"}, {.chars = "ば"}, {.chars = "い"}, {.chars = "い"}, {.chars = "の"}, };
LYRICS_RENDERER(12, lyrics12, 100)

const Char32 lyrics13[12] = { {.chars = "戸"}, {.chars = "惑"}, {.chars = "う"}, {.chars = "言"}, {.chars = "葉"}, {.code = 0}, {.chars = "与"}, {.chars = "え"}, {.chars = "ら"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "も"}, };
LYRICS_RENDERER(13, lyrics13, 100)

const Char32 lyrics14[10] = { {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "心"}, {.code = 0}, {.chars = "た"}, {.chars = "だ"}, {.chars = "上"}, {.chars = "の"}, {.chars = "空"}, };
LYRICS_RENDERER(14, lyrics14, 100)

const Char32 lyrics15[12] = { {.chars = "も"}, {.chars = "し"}, {.chars = "私"}, {.chars = "か"}, {.chars = "ら"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(15, lyrics15, 100)

const Char32 lyrics16[14] = { {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "変"}, {.chars = "え"}, {.chars = "る"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.code = 0}, {.chars = "黒"}, {.chars = "に"}, {.chars = "す"}, {.chars = "る"}, };
LYRICS_RENDERER(16, lyrics16, 100)

const Char32 lyrics17[14] = { {.chars = "こ"}, {.chars = "ん"}, {.chars = "な"}, {.chars = "自"}, {.chars = "分"}, {.chars = "に"}, {.code = 0}, {.chars = "未"}, {.chars = "来"}, {.chars = "は"}, {.chars = "あ"}, {.chars = "る"}, {.chars = "の"}, {.chars = "？"}, };
LYRICS_RENDERER(17, lyrics17, 100)

const Char32 lyrics18[13] = { {.chars = "こ"}, {.chars = "ん"}, {.chars = "な"}, {.chars = "世"}, {.chars = "界"}, {.chars = "に"}, {.code = 0}, {.chars = "私"}, {.chars = "は"}, {.chars = "い"}, {.chars = "る"}, {.chars = "の"}, {.chars = "？"}, };
LYRICS_RENDERER(18, lyrics18, 100)

const Char32 lyrics19[13] = { {.chars = "今"}, {.chars = "切"}, {.chars = "な"}, {.chars = "い"}, {.chars = "の"}, {.chars = "？"}, {.code = 0}, {.chars = "今"}, {.chars = "悲"}, {.chars = "し"}, {.chars = "い"}, {.chars = "の"}, {.chars = "？"}, };
LYRICS_RENDERER(19, lyrics19, 100)

const Char32 lyrics20[14] = { {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.code = 0}, {.chars = "解"}, {.chars = "か"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, {.chars = "ま"}, {.chars = "ま"}, };
LYRICS_RENDERER(20, lyrics20, 100)

const Char32 lyrics21[13] = { {.chars = "歩"}, {.chars = "む"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "さ"}, {.chars = "え"}, {.code = 0}, {.chars = "疲"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "だ"}, {.chars = "け"}, {.chars = "よ"}, };
LYRICS_RENDERER(21, lyrics21, 100)

const Char32 lyrics22[14] = { {.chars = "人"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "な"}, {.chars = "ど"}, {.code = 0}, {.chars = "知"}, {.chars = "り"}, {.chars = "も"}, {.chars = "し"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, };
LYRICS_RENDERER(22, lyrics22, 100)

const Char32 lyrics23[13] = { {.chars = "こ"}, {.chars = "ん"}, {.chars = "な"}, {.chars = "私"}, {.chars = "も"}, {.code = 0}, {.chars = "変"}, {.chars = "わ"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, };
LYRICS_RENDERER(23, lyrics23, 100)

const Char32 lyrics24[14] = { {.chars = "も"}, {.chars = "し"}, {.chars = "変"}, {.chars = "わ"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.code = 0}, {.chars = "白"}, {.chars = "に"}, {.chars = "な"}, {.chars = "る"}, };
LYRICS_RENDERER(24, lyrics24, 100)

const Char32 lyrics25[12] = { {.chars = "流"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "く"}, {.code = 0}, {.chars = "時"}, {.chars = "の"}, {.chars = "中"}, {.chars = "で"}, {.chars = "で"}, {.chars = "も"}, {.code = 0}, };
LYRICS_RENDERER(25, lyrics25, 100)

const Char32 lyrics26[15] = { {.chars = "気"}, {.chars = "だ"}, {.chars = "る"}, {.chars = "さ"}, {.chars = "が"}, {.chars = "ほ"}, {.chars = "ら"}, {.code = 0}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "廻"}, {.chars = "っ"}, {.chars = "て"}, };
LYRICS_RENDERER(26, lyrics26, 100)

const Char32 lyrics27[13] = { {.chars = "私"}, {.chars = "か"}, {.chars = "ら"}, {.chars = "離"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "心"}, {.chars = "も"}, {.chars = "見"}, {.chars = "え"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, };
LYRICS_RENDERER(27, lyrics27, 100)

const Char32 lyrics28[6] = { {.chars = "そ"}, {.chars = "う"}, {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, };
LYRICS_RENDERER(28, lyrics28, 100)

const Char32 lyrics29[12] = { {.chars = "自"}, {.chars = "分"}, {.chars = "か"}, {.chars = "ら"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.chars = "な"}, {.chars = "く"}, };
LYRICS_RENDERER(29, lyrics29, 100)

const Char32 lyrics30[12] = { {.chars = "時"}, {.chars = "の"}, {.chars = "隙"}, {.chars = "間"}, {.chars = "に"}, {.code = 0}, {.chars = "流"}, {.chars = "さ"}, {.chars = "れ"}, {.chars = "続"}, {.chars = "け"}, {.chars = "て"}, };
LYRICS_RENDERER(30, lyrics30, 100)

const Char32 lyrics31[13] = { {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, {.code = 0}, {.chars = "周"}, {.chars = "り"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "な"}, {.chars = "ど"}, };
LYRICS_RENDERER(31, lyrics31, 100)

const Char32 lyrics32[7] = { {.chars = "私"}, {.chars = "は"}, {.chars = "私"}, {.chars = "そ"}, {.chars = "れ"}, {.chars = "だ"}, {.chars = "け"}, };
LYRICS_RENDERER(32, lyrics32, 100)

const Char32 lyrics33[13] = { {.chars = "夢"}, {.chars = "見"}, {.chars = "て"}, {.chars = "る"}, {.chars = "？"}, {.code = 0}, {.chars = "何"}, {.chars = "も"}, {.chars = "見"}, {.chars = "て"}, {.chars = "な"}, {.chars = "い"}, {.chars = "？"}, };
LYRICS_RENDERER(33, lyrics33, 100)

const Char32 lyrics34[12] = { {.chars = "語"}, {.chars = "る"}, {.chars = "も"}, {.chars = "無"}, {.chars = "駄"}, {.chars = "な"}, {.code = 0}, {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "言"}, {.chars = "葉"}, };
LYRICS_RENDERER(34, lyrics34, 100)

const Char32 lyrics35[13] = { {.chars = "悲"}, {.chars = "し"}, {.chars = "む"}, {.chars = "な"}, {.chars = "ん"}, {.chars = "て"}, {.code = 0}, {.chars = "疲"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "だ"}, {.chars = "け"}, {.chars = "よ"}, };
LYRICS_RENDERER(35, lyrics35, 100)

const Char32 lyrics36[13] = { {.chars = "何"}, {.chars = "も"}, {.chars = "感"}, {.chars = "じ"}, {.chars = "ず"}, {.code = 0}, {.chars = "過"}, {.chars = "ご"}, {.chars = "せ"}, {.chars = "ば"}, {.chars = "い"}, {.chars = "い"}, {.chars = "の"}, };
LYRICS_RENDERER(36, lyrics36, 100)

const Char32 lyrics37[12] = { {.chars = "戸"}, {.chars = "惑"}, {.chars = "う"}, {.chars = "言"}, {.chars = "葉"}, {.code = 0}, {.chars = "与"}, {.chars = "え"}, {.chars = "ら"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "も"}, };
LYRICS_RENDERER(37, lyrics37, 100)

const Char32 lyrics38[10] = { {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "心"}, {.code = 0}, {.chars = "た"}, {.chars = "だ"}, {.chars = "上"}, {.chars = "の"}, {.chars = "空"}, };
LYRICS_RENDERER(38, lyrics38, 100)

const Char32 lyrics39[12] = { {.chars = "も"}, {.chars = "し"}, {.chars = "私"}, {.chars = "か"}, {.chars = "ら"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(39, lyrics39, 100)

const Char32 lyrics40[14] = { {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "変"}, {.chars = "え"}, {.chars = "る"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.code = 0}, {.chars = "黒"}, {.chars = "に"}, {.chars = "す"}, {.chars = "る"}, };
LYRICS_RENDERER(40, lyrics40, 100)

const Char32 lyrics41[13] = { {.chars = "動"}, {.chars = "く"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(41, lyrics41, 100)

const Char32 lyrics42[13] = { {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "壊"}, {.chars = "す"}, {.chars = "わ"}, {.code = 0}, {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "壊"}, {.chars = "す"}, {.chars = "わ"}, };
LYRICS_RENDERER(42, lyrics42, 100)

const Char32 lyrics43[13] = { {.chars = "悲"}, {.chars = "し"}, {.chars = "む"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, {.code = 0}, {.chars = "悲"}, {.chars = "し"}, {.chars = "む"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(43, lyrics43, 100)

const Char32 lyrics44[11] = { {.chars = "私"}, {.chars = "の"}, {.chars = "心"}, {.code = 0}, {.chars = "白"}, {.chars = "く"}, {.chars = "変"}, {.chars = "わ"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "？"}, };
LYRICS_RENDERER(44, lyrics44, 100)

const Char32 lyrics45[12] = { {.chars = "貴"}, {.chars = "方"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.code = 0}, {.chars = "私"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, };
LYRICS_RENDERER(45, lyrics45, 100)

const Char32 lyrics46[14] = { {.chars = "全"}, {.chars = "て"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.code = 0}, {.chars = "ま"}, {.chars = "だ"}, {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, {.chars = "の"}, };
LYRICS_RENDERER(46, lyrics46, 100)

const Char32 lyrics47[13] = { {.chars = "重"}, {.chars = "い"}, {.chars = "目"}, {.chars = "蓋"}, {.chars = "を"}, {.code = 0}, {.chars = "開"}, {.chars = "け"}, {.chars = "た"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(47, lyrics47, 100)

const Char32 lyrics48[13] = { {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "壊"}, {.chars = "す"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.code = 0}, {.chars = "黒"}, {.chars = "に"}, {.chars = "な"}, {.chars = "れ"}, };
LYRICS_RENDERER(48, lyrics48, 100)
