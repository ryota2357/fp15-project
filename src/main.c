#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "badapple.h"
#include "bitset128.h"
#include "color.h"
#include "font_bitmap.h"
#include "frame.h"
#include "movie.h"

#define LYRICS_RENDERER_PROTOTYPE_DEFINITION(number) void lyrics_renderer##number(const Frame* const frame, const uint32_t time);
LYRICS_RENDERER_PROTOTYPE_DEFINITION(00) LYRICS_RENDERER_PROTOTYPE_DEFINITION(01) LYRICS_RENDERER_PROTOTYPE_DEFINITION(02) LYRICS_RENDERER_PROTOTYPE_DEFINITION(03) LYRICS_RENDERER_PROTOTYPE_DEFINITION(04) LYRICS_RENDERER_PROTOTYPE_DEFINITION(05) LYRICS_RENDERER_PROTOTYPE_DEFINITION(06) LYRICS_RENDERER_PROTOTYPE_DEFINITION(07) LYRICS_RENDERER_PROTOTYPE_DEFINITION(08) LYRICS_RENDERER_PROTOTYPE_DEFINITION(09)
LYRICS_RENDERER_PROTOTYPE_DEFINITION(10) LYRICS_RENDERER_PROTOTYPE_DEFINITION(11) LYRICS_RENDERER_PROTOTYPE_DEFINITION(12) LYRICS_RENDERER_PROTOTYPE_DEFINITION(13) LYRICS_RENDERER_PROTOTYPE_DEFINITION(14) LYRICS_RENDERER_PROTOTYPE_DEFINITION(15) LYRICS_RENDERER_PROTOTYPE_DEFINITION(16) LYRICS_RENDERER_PROTOTYPE_DEFINITION(17) LYRICS_RENDERER_PROTOTYPE_DEFINITION(18) LYRICS_RENDERER_PROTOTYPE_DEFINITION(19)
LYRICS_RENDERER_PROTOTYPE_DEFINITION(20) LYRICS_RENDERER_PROTOTYPE_DEFINITION(21) LYRICS_RENDERER_PROTOTYPE_DEFINITION(22) LYRICS_RENDERER_PROTOTYPE_DEFINITION(23) LYRICS_RENDERER_PROTOTYPE_DEFINITION(24) LYRICS_RENDERER_PROTOTYPE_DEFINITION(25) LYRICS_RENDERER_PROTOTYPE_DEFINITION(26) LYRICS_RENDERER_PROTOTYPE_DEFINITION(27) LYRICS_RENDERER_PROTOTYPE_DEFINITION(28) LYRICS_RENDERER_PROTOTYPE_DEFINITION(29)
LYRICS_RENDERER_PROTOTYPE_DEFINITION(30) LYRICS_RENDERER_PROTOTYPE_DEFINITION(31) LYRICS_RENDERER_PROTOTYPE_DEFINITION(32) LYRICS_RENDERER_PROTOTYPE_DEFINITION(33) LYRICS_RENDERER_PROTOTYPE_DEFINITION(34) LYRICS_RENDERER_PROTOTYPE_DEFINITION(35) LYRICS_RENDERER_PROTOTYPE_DEFINITION(36) LYRICS_RENDERER_PROTOTYPE_DEFINITION(37) LYRICS_RENDERER_PROTOTYPE_DEFINITION(38) LYRICS_RENDERER_PROTOTYPE_DEFINITION(39)
LYRICS_RENDERER_PROTOTYPE_DEFINITION(40) LYRICS_RENDERER_PROTOTYPE_DEFINITION(41) LYRICS_RENDERER_PROTOTYPE_DEFINITION(42) LYRICS_RENDERER_PROTOTYPE_DEFINITION(43) LYRICS_RENDERER_PROTOTYPE_DEFINITION(44) LYRICS_RENDERER_PROTOTYPE_DEFINITION(45) LYRICS_RENDERER_PROTOTYPE_DEFINITION(46) LYRICS_RENDERER_PROTOTYPE_DEFINITION(47)

void badapple_renderer(const Frame* const frame, const uint32_t time);
void fadein_renderer(const Frame* const frame, const uint32_t time);
void credit_renderer(const Frame* const frame, const uint32_t time);

const uint32_t lyrics_start[48] = {
    873,   // 00 流れてく　時の中ででも
    966,   // 01 気だるさがほらグルグル廻って
    1066,  // 02 私から離れる心も見えないわ
    1212,  // 03 そう知らない
    1290,  // 04 自分から　動くこともなく
    1386,  // 05 時の隙間に　流され続けて
    1484,  // 06 知らないわ　周りのことなど
    1596,  // 07 私は私それだけ
    1698,  // 08 夢見てる？　何も見てない？
    1799,  // 09 語るも無駄な　自分の言葉
    1896,  // 10 悲しむなんて　疲れるだけよ
    1992,  // 11 何も感じず　過ごせばいいの
    2106,  // 12 戸惑う言葉　与えられても
    2204,  // 13 自分の心　ただ上の空
    2316,  // 14 もし私から　動くのならば
    2414,  // 15 すべて変えるのなら　黒にする
    2526,  // 16 こんな自分に　未来はあるの？
    2622,  // 17 こんな世界に　私はいるの？
    2736,  // 18 今切ないの？　今悲しいの？
    2830,  // 19 自分のことも　解からないまま
    2946,  // 20 歩むことさえ　疲れるだけよ
    3043,  // 21 人のことなど　知りもしないわ
    3156,  // 22 こんな私も　変われるのなら
    3251,  // 23 もし変われるのなら　白になる
    3788,  // 24 流れてく　時の中ででも
    3900,  // 25 気だるさがほら　グルグル廻っ
    3997,  // 26 私から離れる心も見えないわ
    4147,  // 27 そう知らない
    4207,  // 28 自分から　動くこともなく
    4302,  // 29 時の隙間に　流され続けて
    4417,  // 30 知らないわ　周りのことなど
    4512,  // 31 私は私それだけ
    4627,  // 32 夢見てる？　何も見てない？
    4717,  // 33 語るも無駄な　自分の言葉
    4815,  // 34 悲しむなんて　疲れるだけよ
    4927,  // 35 何も感じず　過ごせばいいの
    5023,  // 36 戸惑う言葉　与えられても
    5136,  // 37 自分の心　ただ上の空
    5230,  // 38 もし私から　動くのならば
    5349,  // 39 すべて変えるのなら　黒にする
    5440,  // 40 動くのならば　動くのならば
    5556,  // 41 すべて壊すわ　すべて壊すわ
    5654,  // 42 悲しむならば　悲しむならば
    5763,  // 43 私の心　白く変われる？
    5860,  // 44 貴方のことも　私のことも
    5974,  // 45 全てのことも　まだ知らないの
    6070,  // 46 重い目蓋を　開けたのならば
    6183,  // 47 すべて壊すのなら　黒になれ
};

int main(int argc, char* args[]) {
    if (argc != 2) {
        fprintf(stderr, "Argument Error, the number of argument must be 2 but %d\n", argc);
        exit(1);
    }
    const char* build_dir = args[1];
    const bool short_movie = false;

    font_bitmap_init();
    badapple_init();

    Movie movie = Movie_new(
        BADAPPLE_FRAME_WIDTH * 4,
        BADAPPLE_FRAME_HEIGHT * 4,
        short_movie ? 2000 + 30 : BADAPPLE_FRAME_COUNT + 30
    );

    Movie_add_renderer(&movie, badapple_renderer, 0);
    Movie_add_renderer(&movie, lyrics_renderer00, lyrics_start[0]);
    Movie_add_renderer(&movie, lyrics_renderer01, lyrics_start[1]);
    Movie_add_renderer(&movie, lyrics_renderer02, lyrics_start[2]);
    Movie_add_renderer(&movie, lyrics_renderer03, lyrics_start[3]);
    Movie_add_renderer(&movie, lyrics_renderer04, lyrics_start[4]);
    Movie_add_renderer(&movie, lyrics_renderer05, lyrics_start[5]);
    Movie_add_renderer(&movie, lyrics_renderer06, lyrics_start[6]);
    Movie_add_renderer(&movie, lyrics_renderer07, lyrics_start[7]);
    Movie_add_renderer(&movie, lyrics_renderer08, lyrics_start[8]);
    Movie_add_renderer(&movie, lyrics_renderer09, lyrics_start[9]);
    Movie_add_renderer(&movie, lyrics_renderer10, lyrics_start[10]);
    Movie_add_renderer(&movie, lyrics_renderer11, lyrics_start[11]);
    Movie_add_renderer(&movie, lyrics_renderer12, lyrics_start[12]);
    Movie_add_renderer(&movie, lyrics_renderer13, lyrics_start[13]);
    Movie_add_renderer(&movie, lyrics_renderer14, lyrics_start[14]);
    Movie_add_renderer(&movie, lyrics_renderer15, lyrics_start[15]);
    Movie_add_renderer(&movie, lyrics_renderer16, lyrics_start[16]);
    Movie_add_renderer(&movie, lyrics_renderer17, lyrics_start[17]);
    Movie_add_renderer(&movie, lyrics_renderer18, lyrics_start[18]);
    Movie_add_renderer(&movie, lyrics_renderer19, lyrics_start[19]);
    Movie_add_renderer(&movie, lyrics_renderer20, lyrics_start[20]);
    Movie_add_renderer(&movie, lyrics_renderer21, lyrics_start[21]);
    Movie_add_renderer(&movie, lyrics_renderer22, lyrics_start[22]);
    Movie_add_renderer(&movie, lyrics_renderer23, lyrics_start[23]);
    Movie_add_renderer(&movie, lyrics_renderer24, lyrics_start[24]);
    Movie_add_renderer(&movie, lyrics_renderer25, lyrics_start[25]);
    Movie_add_renderer(&movie, lyrics_renderer26, lyrics_start[26]);
    Movie_add_renderer(&movie, lyrics_renderer27, lyrics_start[27]);
    Movie_add_renderer(&movie, lyrics_renderer28, lyrics_start[28]);
    Movie_add_renderer(&movie, lyrics_renderer29, lyrics_start[29]);
    Movie_add_renderer(&movie, lyrics_renderer30, lyrics_start[30]);
    Movie_add_renderer(&movie, lyrics_renderer31, lyrics_start[31]);
    Movie_add_renderer(&movie, lyrics_renderer32, lyrics_start[32]);
    Movie_add_renderer(&movie, lyrics_renderer33, lyrics_start[33]);
    Movie_add_renderer(&movie, lyrics_renderer34, lyrics_start[34]);
    Movie_add_renderer(&movie, lyrics_renderer35, lyrics_start[35]);
    Movie_add_renderer(&movie, lyrics_renderer36, lyrics_start[36]);
    Movie_add_renderer(&movie, lyrics_renderer37, lyrics_start[37]);
    Movie_add_renderer(&movie, lyrics_renderer38, lyrics_start[38]);
    Movie_add_renderer(&movie, lyrics_renderer39, lyrics_start[39]);
    Movie_add_renderer(&movie, lyrics_renderer40, lyrics_start[40]);
    Movie_add_renderer(&movie, lyrics_renderer41, lyrics_start[41]);
    Movie_add_renderer(&movie, lyrics_renderer42, lyrics_start[42]);
    Movie_add_renderer(&movie, lyrics_renderer43, lyrics_start[43]);
    Movie_add_renderer(&movie, lyrics_renderer44, lyrics_start[44]);
    Movie_add_renderer(&movie, lyrics_renderer45, lyrics_start[45]);
    Movie_add_renderer(&movie, lyrics_renderer46, lyrics_start[46]);
    Movie_add_renderer(&movie, lyrics_renderer47, lyrics_start[47]);

    if (short_movie) {
        Movie_add_renderer(&movie, fadein_renderer, 2000 - 60);
        Movie_add_renderer(&movie, credit_renderer, 2000);
    } else {
        Movie_add_renderer(&movie, credit_renderer, BADAPPLE_FRAME_COUNT);
    }

    Movie_build(&movie, build_dir);
    /* Movie_debug_build(&movie, build_dir, 1000, 1500); */
    Movie_free(&movie);

    return 0;
}

// reference: https://qiita.com/yoya/items/f167b2598fec98679422
void badapple_renderer(const Frame* const frame, const uint32_t time) {
    if (time >= BADAPPLE_FRAME_COUNT) {
        return;
    }
    BadAppleFrame apple = badapple_get(time);
    const uint16_t scale_width = 4;
    const uint16_t scale_height = 4;

    const int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    const int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    for (uint16_t x = 0; x < scale_width * BADAPPLE_FRAME_WIDTH; ++x) {
        for (uint16_t y = 0; y < scale_height * BADAPPLE_FRAME_HEIGHT; ++y) {
            uint16_t base_x = x / scale_width;
            uint16_t base_y = y / scale_height;
            double sum_color = 0;
            double sum_weight = 0;
            for (int dir = 0; dir < 9; ++dir) {
                uint16_t original_x = base_x + dx[dir];
                uint16_t original_y = base_y + dy[dir];
                if (BADAPPLE_FRAME_WIDTH <= original_x) {
                    continue;
                }
                if (BADAPPLE_FRAME_HEIGHT <= original_y) {
                    continue;
                }
                double dist = pow(x - original_x * scale_width, 2) + pow(y - original_y * scale_height, 2) + 1.0;
                double weight = 1.0 / dist;
                if (scale_width * scale_width + scale_height * scale_height < dist) {
                   continue;
                }
                sum_weight += weight;
                if (BitSet128_is_1(&apple.lines[original_y], original_x)) {
                    sum_color += 255.0 * weight;
                }
            }
            sum_color /= sum_weight;
            uint8_t color = sum_color + 0.5;
            Frame_draw(frame, x, y, color_new(color, color, color));
        }
    }
}

void fadein_renderer(const Frame* const frame, const uint32_t time) {
    const double speed = 255.0 / 60;
    const uint16_t width = frame->width;
    const uint16_t height = frame->height;
    for (uint16_t x = 0; x < width; ++x) {
        for (uint16_t y = 0; y < height; ++y) {
            double level = fmin(255, speed * time);
            Color color = Frame_at(frame, x, y);
            uint8_t r = color.r - level < 0 ? 0 : color.r - level;
            uint8_t g = color.g - level < 0 ? 0 : color.g - level;
            uint8_t b = color.b - level < 0 ? 0 : color.b - level;
            Frame_draw(frame, x, y, color_new(r, g, b));
        }
    }
}

void draw_char_at(const Frame* const frame,
                  const Char32 ch,
                  const uint16_t reduction_width,
                  const uint16_t reduction_height,
                  const uint16_t posx,
                  const uint16_t posy) {
    const double mid_x = (double) reduction_width / 2;
    const double mid_y = (double) reduction_height / 2;

    CharBitMap map = font_bitmap_get(ch);
    for (uint16_t y = 0; y < (TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE / reduction_height); ++y) {
        for (uint16_t x = 0; x < (TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE / reduction_width); ++x) {
            double sum_color = 0;
            double sum_weight = 0;
            for (int i = 0; i < reduction_width; ++i) for (int j = 0; j < reduction_height; ++j) {
                double dist = pow(i - mid_x, 2) + pow(y - mid_y, 2) + 1.0;
                double weight = 1.0 / dist;
                uint16_t flag = (map.bitmap[reduction_width * y + i] & (1ll << (reduction_height * x + j)) ? 1 : 0);
                sum_weight += weight;
                sum_color += (double) flag * weight;
            }
            if (sum_color < sum_weight * 0.5) {
                continue;
            }
            Color frame_color = Frame_at(frame, posx + x, posy + y);
            uint32_t ave = ((uint32_t) frame_color.r + frame_color.g + frame_color.b) / 3;
            Frame_draw(frame, posx + x, posy + y, color_new(255 - ave, 255 - ave, 255 - ave));
        }
    }
}
void credit_renderer(const Frame* const frame, const uint32_t time) {
    // fill background
    const Color bg_color = color_new(15, 15, 25);
    if (time < 15) {
        double rate = time / 15.0;
        for (uint16_t x = 0; x < frame->width; ++x) for (uint16_t y = 0; y < frame->height; ++y) {
            uint8_t r = bg_color.r * rate;
            uint8_t g = bg_color.g * rate;
            uint8_t b = bg_color.b * rate;
            Frame_draw(frame, x, y, color_new(r, g, b));
        }
        return;
    }
    for (uint16_t x = 0; x < frame->width; ++x) for (uint16_t y = 0; y < frame->height; ++y) {
        Frame_draw(frame, x, y, bg_color);
    }

    // 1: Bad Apple!!
    // 2: Repository (GitHub):
    // 3    ryota2357/fp15-project
    // 4: Animation Frame Data (GitHub):
    // 5    Reyansh-Khobragade/bad-apple-nodejs
    // 6: Font: Noto Sans JP
    // 7: Developer: ryota2357, dyktr_06
    const Char32 line1[11] = { {.chars = "B"}, {.chars = "a"}, {.chars = "d"}, {.code = 0}, {.chars = "A"}, {.chars = "p"}, {.chars = "p"}, {.chars = "l"}, {.chars = "e"}, {.chars = "!"}, {.chars = "!"}, };
    const Char32 line2[20] = { {.chars = "R"}, {.chars = "e"}, {.chars = "p"}, {.chars = "o"}, {.chars = "s"}, {.chars = "i"}, {.chars = "t"}, {.chars = "o"}, {.chars = "r"}, {.chars = "y"}, {.code = 0}, {.chars = "("}, {.chars = "G"}, {.chars = "i"}, {.chars = "t"}, {.chars = "H"}, {.chars = "u"}, {.chars = "b"}, {.chars = ")"}, {.chars = ":"}, };
    const Char32 line3[24] = { {.code = 0}, {.code = 0}, {.chars = "r"}, {.chars = "y"}, {.chars = "o"}, {.chars = "t"}, {.chars = "a"}, {.chars = "2"}, {.chars = "3"}, {.chars = "5"}, {.chars = "7"}, {.chars = "/"}, {.chars = "f"}, {.chars = "p"}, {.chars = "1"}, {.chars = "5"}, {.chars = "-"}, {.chars = "p"}, {.chars = "r"}, {.chars = "o"}, {.chars = "j"}, {.chars = "e"}, {.chars = "c"}, {.chars = "t"}, };
    const Char32 line4[30] = { {.chars = "A"}, {.chars = "n"}, {.chars = "i"}, {.chars = "m"}, {.chars = "a"}, {.chars = "t"}, {.chars = "i"}, {.chars = "o"}, {.chars = "n"}, {.code = 0}, {.chars = "F"}, {.chars = "r"}, {.chars = "a"}, {.chars = "m"}, {.chars = "e"}, {.code = 0}, {.chars = "D"}, {.chars = "a"}, {.chars = "t"}, {.chars = "a"}, {.code = 0}, {.chars = "("}, {.chars = "G"}, {.chars = "i"}, {.chars = "t"}, {.chars = "H"}, {.chars = "u"}, {.chars = "b"}, {.chars = ")"}, {.chars = ":"}, };
    const Char32 line5[37] = { {.code = 0}, {.code = 0}, {.chars = "R"}, {.chars = "e"}, {.chars = "y"}, {.chars = "a"}, {.chars = "n"}, {.chars = "s"}, {.chars = "h"}, {.chars = "-"}, {.chars = "K"}, {.chars = "h"}, {.chars = "o"}, {.chars = "b"}, {.chars = "r"}, {.chars = "a"}, {.chars = "g"}, {.chars = "a"}, {.chars = "d"}, {.chars = "e"}, {.chars = "/"}, {.chars = "b"}, {.chars = "a"}, {.chars = "d"}, {.chars = "-"}, {.chars = "a"}, {.chars = "p"}, {.chars = "p"}, {.chars = "l"}, {.chars = "e"}, {.chars = "-"}, {.chars = "n"}, {.chars = "o"}, {.chars = "d"}, {.chars = "e"}, {.chars = "j"}, {.chars = "s"}, };
    const Char32 line6[18] = { {.chars = "F"}, {.chars = "o"}, {.chars = "n"}, {.chars = "t"}, {.chars = ":"}, {.code = 0}, {.chars = "N"}, {.chars = "o"}, {.chars = "t"}, {.chars = "o"}, {.code = 0}, {.chars = "S"}, {.chars = "a"}, {.chars = "n"}, {.chars = "s"}, {.code = 0}, {.chars = "J"}, {.chars = "P"}, };
    const Char32 line7[30] = { {.chars = "D"}, {.chars = "e"}, {.chars = "v"}, {.chars = "e"}, {.chars = "l"}, {.chars = "o"}, {.chars = "p"}, {.chars = "e"}, {.chars = "r"}, {.chars = ":"}, {.code = 0}, {.chars = "r"}, {.chars = "y"}, {.chars = "o"}, {.chars = "t"}, {.chars = "a"}, {.chars = "2"}, {.chars = "3"}, {.chars = "5"}, {.chars = "7"}, {.chars = ","}, {.code = 0}, {.chars = "d"}, {.chars = "y"}, {.chars = "k"}, {.chars = "t"}, {.chars = "r"}, {.chars = "_"}, {.chars = "0"}, {.chars = "6"}, };
    #define _credit_renderer_CREDIT_LINE_DRAW(line, posy)               \
        for (size_t i = 0;  i < (sizeof(line) / sizeof(Char32)); ++i) { \
            if (line[i].code == 0) { continue; }                        \
            draw_char_at(frame, line[i], 3, 3, 10 + (i * 9), (posy));   \
        }
    _credit_renderer_CREDIT_LINE_DRAW(line1, 30);
    _credit_renderer_CREDIT_LINE_DRAW(line2, 55);
    _credit_renderer_CREDIT_LINE_DRAW(line3, 80);
    _credit_renderer_CREDIT_LINE_DRAW(line4, 105);
    _credit_renderer_CREDIT_LINE_DRAW(line5, 130);
    _credit_renderer_CREDIT_LINE_DRAW(line6, 155);
    _credit_renderer_CREDIT_LINE_DRAW(line7, 180);
}

#define LYRICS_RENDERER(number, words, duration)                                        \
    void lyrics_renderer##number(const Frame* const frame, const uint32_t time) {       \
        if (time >= (duration)) return;                                                 \
        const uint16_t size = sizeof(words) / sizeof(words[0]);                         \
        const uint16_t width = frame->width;                                            \
        for (int i = -(size / 2); i < (size + 1) / 2; ++i) {                            \
            int idx = i + (size / 2);                                                   \
            if (words[idx].code == 0) continue;                                         \
            uint16_t x = (width / 2) + (20 * i);                                        \
            draw_char_at(frame, words[idx], 2, 2, x, (BADAPPLE_FRAME_HEIGHT * 4) - 30); \
        }                                                                               \
    }

const Char32 lyrics00[11] = { {.chars = "流"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "く"}, {.code = 0}, {.chars = "時"}, {.chars = "の"}, {.chars = "中"}, {.chars = "で"}, {.chars = "で"}, {.chars = "も"}, };
LYRICS_RENDERER(00, lyrics00, lyrics_start[1] - lyrics_start[0])

const Char32 lyrics01[14] = { {.chars = "気"}, {.chars = "だ"}, {.chars = "る"}, {.chars = "さ"}, {.chars = "が"}, {.chars = "ほ"}, {.chars = "ら"}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "廻"}, {.chars = "っ"}, {.chars = "て"}, };
LYRICS_RENDERER(01, lyrics01, lyrics_start[2] - lyrics_start[1])

const Char32 lyrics02[13] = { {.chars = "私"}, {.chars = "か"}, {.chars = "ら"}, {.chars = "離"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "心"}, {.chars = "も"}, {.chars = "見"}, {.chars = "え"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, };
LYRICS_RENDERER(02, lyrics02, lyrics_start[3] - lyrics_start[2])

const Char32 lyrics03[6] = { {.chars = "そ"}, {.chars = "う"}, {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, };
LYRICS_RENDERER(03, lyrics03, lyrics_start[4] - lyrics_start[3])

const Char32 lyrics04[12] = { {.chars = "自"}, {.chars = "分"}, {.chars = "か"}, {.chars = "ら"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.chars = "な"}, {.chars = "く"}, };
LYRICS_RENDERER(04, lyrics04, lyrics_start[5] - lyrics_start[4])

const Char32 lyrics05[12] = { {.chars = "時"}, {.chars = "の"}, {.chars = "隙"}, {.chars = "間"}, {.chars = "に"}, {.code = 0}, {.chars = "流"}, {.chars = "さ"}, {.chars = "れ"}, {.chars = "続"}, {.chars = "け"}, {.chars = "て"}, };
LYRICS_RENDERER(05, lyrics05, lyrics_start[6] - lyrics_start[5])

const Char32 lyrics06[13] = { {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, {.code = 0}, {.chars = "周"}, {.chars = "り"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "な"}, {.chars = "ど"}, };
LYRICS_RENDERER(06, lyrics06, lyrics_start[7] - lyrics_start[6])

const Char32 lyrics07[7] = { {.chars = "私"}, {.chars = "は"}, {.chars = "私"}, {.chars = "そ"}, {.chars = "れ"}, {.chars = "だ"}, {.chars = "け"}, };
LYRICS_RENDERER(07, lyrics07, lyrics_start[8] - lyrics_start[7])

const Char32 lyrics08[13] = { {.chars = "夢"}, {.chars = "見"}, {.chars = "て"}, {.chars = "る"}, {.chars = "？"}, {.code = 0}, {.chars = "何"}, {.chars = "も"}, {.chars = "見"}, {.chars = "て"}, {.chars = "な"}, {.chars = "い"}, {.chars = "？"}, };
LYRICS_RENDERER(08, lyrics08, lyrics_start[9] - lyrics_start[8])

const Char32 lyrics09[12] = { {.chars = "語"}, {.chars = "る"}, {.chars = "も"}, {.chars = "無"}, {.chars = "駄"}, {.chars = "な"}, {.code = 0}, {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "言"}, {.chars = "葉"}, };
LYRICS_RENDERER(09, lyrics09, lyrics_start[10] - lyrics_start[9])

const Char32 lyrics10[13] = { {.chars = "悲"}, {.chars = "し"}, {.chars = "む"}, {.chars = "な"}, {.chars = "ん"}, {.chars = "て"}, {.code = 0}, {.chars = "疲"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "だ"}, {.chars = "け"}, {.chars = "よ"}, };
LYRICS_RENDERER(10, lyrics10, lyrics_start[11] - lyrics_start[10])

const Char32 lyrics11[13] = { {.chars = "何"}, {.chars = "も"}, {.chars = "感"}, {.chars = "じ"}, {.chars = "ず"}, {.code = 0}, {.chars = "過"}, {.chars = "ご"}, {.chars = "せ"}, {.chars = "ば"}, {.chars = "い"}, {.chars = "い"}, {.chars = "の"}, };
LYRICS_RENDERER(11, lyrics11, lyrics_start[12] - lyrics_start[11])

const Char32 lyrics12[12] = { {.chars = "戸"}, {.chars = "惑"}, {.chars = "う"}, {.chars = "言"}, {.chars = "葉"}, {.code = 0}, {.chars = "与"}, {.chars = "え"}, {.chars = "ら"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "も"}, };
LYRICS_RENDERER(12, lyrics12, lyrics_start[13] - lyrics_start[12])

const Char32 lyrics13[10] = { {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "心"}, {.code = 0}, {.chars = "た"}, {.chars = "だ"}, {.chars = "上"}, {.chars = "の"}, {.chars = "空"}, };
LYRICS_RENDERER(13, lyrics13, lyrics_start[14] - lyrics_start[13])

const Char32 lyrics14[12] = { {.chars = "も"}, {.chars = "し"}, {.chars = "私"}, {.chars = "か"}, {.chars = "ら"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(14, lyrics14, lyrics_start[15] - lyrics_start[14])

const Char32 lyrics15[14] = { {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "変"}, {.chars = "え"}, {.chars = "る"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.code = 0}, {.chars = "黒"}, {.chars = "に"}, {.chars = "す"}, {.chars = "る"}, };
LYRICS_RENDERER(15, lyrics15, lyrics_start[16] - lyrics_start[15])

const Char32 lyrics16[14] = { {.chars = "こ"}, {.chars = "ん"}, {.chars = "な"}, {.chars = "自"}, {.chars = "分"}, {.chars = "に"}, {.code = 0}, {.chars = "未"}, {.chars = "来"}, {.chars = "は"}, {.chars = "あ"}, {.chars = "る"}, {.chars = "の"}, {.chars = "？"}, };
LYRICS_RENDERER(16, lyrics16, lyrics_start[17] - lyrics_start[16])

const Char32 lyrics17[13] = { {.chars = "こ"}, {.chars = "ん"}, {.chars = "な"}, {.chars = "世"}, {.chars = "界"}, {.chars = "に"}, {.code = 0}, {.chars = "私"}, {.chars = "は"}, {.chars = "い"}, {.chars = "る"}, {.chars = "の"}, {.chars = "？"}, };
LYRICS_RENDERER(17, lyrics17, lyrics_start[18] - lyrics_start[17])

const Char32 lyrics18[13] = { {.chars = "今"}, {.chars = "切"}, {.chars = "な"}, {.chars = "い"}, {.chars = "の"}, {.chars = "？"}, {.code = 0}, {.chars = "今"}, {.chars = "悲"}, {.chars = "し"}, {.chars = "い"}, {.chars = "の"}, {.chars = "？"}, };
LYRICS_RENDERER(18, lyrics18, lyrics_start[19] - lyrics_start[18])

const Char32 lyrics19[14] = { {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.code = 0}, {.chars = "解"}, {.chars = "か"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, {.chars = "ま"}, {.chars = "ま"}, };
LYRICS_RENDERER(19, lyrics19, lyrics_start[20] - lyrics_start[19])

const Char32 lyrics20[13] = { {.chars = "歩"}, {.chars = "む"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "さ"}, {.chars = "え"}, {.code = 0}, {.chars = "疲"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "だ"}, {.chars = "け"}, {.chars = "よ"}, };
LYRICS_RENDERER(20, lyrics20, lyrics_start[21] - lyrics_start[20])

const Char32 lyrics21[14] = { {.chars = "人"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "な"}, {.chars = "ど"}, {.code = 0}, {.chars = "知"}, {.chars = "り"}, {.chars = "も"}, {.chars = "し"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, };
LYRICS_RENDERER(21, lyrics21, lyrics_start[22] - lyrics_start[21])

const Char32 lyrics22[13] = { {.chars = "こ"}, {.chars = "ん"}, {.chars = "な"}, {.chars = "私"}, {.chars = "も"}, {.code = 0}, {.chars = "変"}, {.chars = "わ"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, };
LYRICS_RENDERER(22, lyrics22, lyrics_start[23] - lyrics_start[22])

const Char32 lyrics23[14] = { {.chars = "も"}, {.chars = "し"}, {.chars = "変"}, {.chars = "わ"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.code = 0}, {.chars = "白"}, {.chars = "に"}, {.chars = "な"}, {.chars = "る"}, };
LYRICS_RENDERER(23, lyrics23, 3322 - lyrics_start[23])

const Char32 lyrics24[12] = { {.chars = "流"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "く"}, {.code = 0}, {.chars = "時"}, {.chars = "の"}, {.chars = "中"}, {.chars = "で"}, {.chars = "で"}, {.chars = "も"}, {.code = 0}, };
LYRICS_RENDERER(24, lyrics24, lyrics_start[25] - lyrics_start[24])

const Char32 lyrics25[15] = { {.chars = "気"}, {.chars = "だ"}, {.chars = "る"}, {.chars = "さ"}, {.chars = "が"}, {.chars = "ほ"}, {.chars = "ら"}, {.code = 0}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "グ"}, {.chars = "ル"}, {.chars = "廻"}, {.chars = "っ"}, {.chars = "て"}, };
LYRICS_RENDERER(25, lyrics25, lyrics_start[26] - lyrics_start[25])

const Char32 lyrics26[13] = { {.chars = "私"}, {.chars = "か"}, {.chars = "ら"}, {.chars = "離"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "心"}, {.chars = "も"}, {.chars = "見"}, {.chars = "え"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, };
LYRICS_RENDERER(26, lyrics26, lyrics_start[27] - lyrics_start[26])

const Char32 lyrics27[6] = { {.chars = "そ"}, {.chars = "う"}, {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, };
LYRICS_RENDERER(27, lyrics27, lyrics_start[28] - lyrics_start[27])

const Char32 lyrics28[12] = { {.chars = "自"}, {.chars = "分"}, {.chars = "か"}, {.chars = "ら"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.chars = "な"}, {.chars = "く"}, };
LYRICS_RENDERER(28, lyrics28, lyrics_start[29] - lyrics_start[28])

const Char32 lyrics29[12] = { {.chars = "時"}, {.chars = "の"}, {.chars = "隙"}, {.chars = "間"}, {.chars = "に"}, {.code = 0}, {.chars = "流"}, {.chars = "さ"}, {.chars = "れ"}, {.chars = "続"}, {.chars = "け"}, {.chars = "て"}, };
LYRICS_RENDERER(29, lyrics29, lyrics_start[30] - lyrics_start[29])

const Char32 lyrics30[13] = { {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, {.chars = "わ"}, {.code = 0}, {.chars = "周"}, {.chars = "り"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "な"}, {.chars = "ど"}, };
LYRICS_RENDERER(30, lyrics30, lyrics_start[31] - lyrics_start[30])

const Char32 lyrics31[7] = { {.chars = "私"}, {.chars = "は"}, {.chars = "私"}, {.chars = "そ"}, {.chars = "れ"}, {.chars = "だ"}, {.chars = "け"}, };
LYRICS_RENDERER(31, lyrics31, lyrics_start[32] - lyrics_start[31])

const Char32 lyrics32[13] = { {.chars = "夢"}, {.chars = "見"}, {.chars = "て"}, {.chars = "る"}, {.chars = "？"}, {.code = 0}, {.chars = "何"}, {.chars = "も"}, {.chars = "見"}, {.chars = "て"}, {.chars = "な"}, {.chars = "い"}, {.chars = "？"}, };
LYRICS_RENDERER(32, lyrics32, lyrics_start[33] - lyrics_start[32])

const Char32 lyrics33[12] = { {.chars = "語"}, {.chars = "る"}, {.chars = "も"}, {.chars = "無"}, {.chars = "駄"}, {.chars = "な"}, {.code = 0}, {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "言"}, {.chars = "葉"}, };
LYRICS_RENDERER(33, lyrics33, lyrics_start[34] - lyrics_start[33])

const Char32 lyrics34[13] = { {.chars = "悲"}, {.chars = "し"}, {.chars = "む"}, {.chars = "な"}, {.chars = "ん"}, {.chars = "て"}, {.code = 0}, {.chars = "疲"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "だ"}, {.chars = "け"}, {.chars = "よ"}, };
LYRICS_RENDERER(34, lyrics34, lyrics_start[35] - lyrics_start[34])

const Char32 lyrics35[13] = { {.chars = "何"}, {.chars = "も"}, {.chars = "感"}, {.chars = "じ"}, {.chars = "ず"}, {.code = 0}, {.chars = "過"}, {.chars = "ご"}, {.chars = "せ"}, {.chars = "ば"}, {.chars = "い"}, {.chars = "い"}, {.chars = "の"}, };
LYRICS_RENDERER(35, lyrics35, lyrics_start[36] - lyrics_start[35])

const Char32 lyrics36[12] = { {.chars = "戸"}, {.chars = "惑"}, {.chars = "う"}, {.chars = "言"}, {.chars = "葉"}, {.code = 0}, {.chars = "与"}, {.chars = "え"}, {.chars = "ら"}, {.chars = "れ"}, {.chars = "て"}, {.chars = "も"}, };
LYRICS_RENDERER(36, lyrics36, lyrics_start[37] - lyrics_start[36])

const Char32 lyrics37[10] = { {.chars = "自"}, {.chars = "分"}, {.chars = "の"}, {.chars = "心"}, {.code = 0}, {.chars = "た"}, {.chars = "だ"}, {.chars = "上"}, {.chars = "の"}, {.chars = "空"}, };
LYRICS_RENDERER(37, lyrics37, lyrics_start[38] - lyrics_start[37])

const Char32 lyrics38[12] = { {.chars = "も"}, {.chars = "し"}, {.chars = "私"}, {.chars = "か"}, {.chars = "ら"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(38, lyrics38, lyrics_start[39] - lyrics_start[38])

const Char32 lyrics39[14] = { {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "変"}, {.chars = "え"}, {.chars = "る"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.code = 0}, {.chars = "黒"}, {.chars = "に"}, {.chars = "す"}, {.chars = "る"}, };
LYRICS_RENDERER(39, lyrics39, lyrics_start[40] - lyrics_start[39])

const Char32 lyrics40[13] = { {.chars = "動"}, {.chars = "く"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, {.code = 0}, {.chars = "動"}, {.chars = "く"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(40, lyrics40, lyrics_start[41] - lyrics_start[40])

const Char32 lyrics41[13] = { {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "壊"}, {.chars = "す"}, {.chars = "わ"}, {.code = 0}, {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "壊"}, {.chars = "す"}, {.chars = "わ"}, };
LYRICS_RENDERER(41, lyrics41, lyrics_start[42] - lyrics_start[41])

const Char32 lyrics42[13] = { {.chars = "悲"}, {.chars = "し"}, {.chars = "む"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, {.code = 0}, {.chars = "悲"}, {.chars = "し"}, {.chars = "む"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(42, lyrics42, lyrics_start[43] - lyrics_start[42])

const Char32 lyrics43[11] = { {.chars = "私"}, {.chars = "の"}, {.chars = "心"}, {.code = 0}, {.chars = "白"}, {.chars = "く"}, {.chars = "変"}, {.chars = "わ"}, {.chars = "れ"}, {.chars = "る"}, {.chars = "？"}, };
LYRICS_RENDERER(43, lyrics43, lyrics_start[44] - lyrics_start[43])

const Char32 lyrics44[12] = { {.chars = "貴"}, {.chars = "方"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.code = 0}, {.chars = "私"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, };
LYRICS_RENDERER(44, lyrics44, lyrics_start[45] - lyrics_start[44])

const Char32 lyrics45[14] = { {.chars = "全"}, {.chars = "て"}, {.chars = "の"}, {.chars = "こ"}, {.chars = "と"}, {.chars = "も"}, {.code = 0}, {.chars = "ま"}, {.chars = "だ"}, {.chars = "知"}, {.chars = "ら"}, {.chars = "な"}, {.chars = "い"}, {.chars = "の"}, };
LYRICS_RENDERER(45, lyrics45, lyrics_start[46] - lyrics_start[45])

const Char32 lyrics46[13] = { {.chars = "重"}, {.chars = "い"}, {.chars = "目"}, {.chars = "蓋"}, {.chars = "を"}, {.code = 0}, {.chars = "開"}, {.chars = "け"}, {.chars = "た"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.chars = "ば"}, };
LYRICS_RENDERER(46, lyrics46, lyrics_start[47] - lyrics_start[46])

const Char32 lyrics47[13] = { {.chars = "す"}, {.chars = "べ"}, {.chars = "て"}, {.chars = "壊"}, {.chars = "す"}, {.chars = "の"}, {.chars = "な"}, {.chars = "ら"}, {.code = 0}, {.chars = "黒"}, {.chars = "に"}, {.chars = "な"}, {.chars = "れ"}, };
LYRICS_RENDERER(47, lyrics47, 6278 - lyrics_start[47])
