#include "../include/badapple.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/free.h"

static bool IsInit = false;
static BadAppleFrame Frames[BADAPPLE_FRAME_COUNT] = {0};

// https://programming-place.net/ppp/contents/c/rev_res/string017.html
static char* substring(const char* target, size_t begin, size_t length, char* result, size_t result_size) {
    assert(target != NULL);
    assert(result != NULL);
    assert(length + 1 <= result_size);
    if (begin < strlen(target)) {
        strncpy(result, target + begin, length);
        result[length] = '\0';
    } else {
        result[0] = '\0';
    }
    return result;
}

static FILE* get_frame_file(void) {
    // search dir
    const char* this_file = __FILE__;
    const int len = strlen(this_file);
    const char* dir_end = strrchr(this_file, '/');
    char* dir = calloc(strlen(this_file), sizeof(char));
    for (int i = 0; i < len; i++) {
        dir[i] = this_file[i];
        if (this_file + i == dir_end) {
            break;
        }
    }

    // get file_name
    const size_t dir_length = strlen(dir);
    char* file_name = calloc(dir_length + 50, sizeof(char));
    char* substr = calloc(dir_length, sizeof(char));  // hoge/fuga/badapple/src/ -> hoge/fuga/badapple/resources/frames2.txt
    sprintf(file_name, "%s/resources/frames.txt", substring(dir, 0, dir_length - 5, substr, dir_length));
    FREE(substr);
    FREE(dir);

    // open file
    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Could not open frames data file: %s\n", file_name);
        FREE(file_name);
        exit(1);
    }
    FREE(file_name);

    return file;
}

void badapple_init(void) {
    FILE* frame_file = get_frame_file();

    char line[200] = {0};
    uint32_t index = 0, bit_line_index = 0;
    while (fgets(line, sizeof(line), frame_file) != NULL) {
        if (line[0] == 'c') {
            // rest to new frame.
            bit_line_index = 0;
            // c:0123
            char s[5];
            index = atoi(substring(line, 2, 4, s, sizeof(s))) - 1;
            continue;
        }
        if (line[0] == 't') {
            // 0123456789012345678901234567890
            // t:00:02:14,533 --> 00:02:14,567
            char s[4] = {0};
            uint32_t time = 0;
            time += atoi(substring(line, 5, 2, s, sizeof(s))) * 60 * 1000;
            time += atoi(substring(line, 8, 2, s, sizeof(s))) * 1000;
            time += atoi(substring(line, 11, 3, s, sizeof(s)));
            Frames[index].start_time = time;
            time = 0;
            time += atoi(substring(line, 22, 2, s, sizeof(s))) * 60 * 1000;
            time += atoi(substring(line, 25, 2, s, sizeof(s))) * 1000;
            time += atoi(substring(line, 28, 3, s, sizeof(s)));
            Frames[index].end_time = time;
            continue;
        }
        if (line[0] == 'b') {
            // 0123456789012
            // b:000,255,123,.....,000
            // length = 2 + (4 * 48(=BADAPPLE_FRAME_HEIGHT/2)) - 1 = 193
            for (uint8_t i = 0; i < BADAPPLE_FRAME_WIDTH / 2; ++i) {
                char s[4] = {0};
                const uint8_t num = atoi(substring(line, (2 + i * 4), 3, s, sizeof(s)));
                // ⓪ ④
                // ① ⑤
                // ② ⑥
                // ③ ⑦
                if (num & (1 << 0)) {
                    BitSet128_set_1(&Frames[index].lines[bit_line_index + 0], 2 * i);
                }
                if (num & (1 << 1)) {
                    BitSet128_set_1(&Frames[index].lines[bit_line_index + 1], 2 * i);
                }
                if (num & (1 << 2)) {
                    BitSet128_set_1(&Frames[index].lines[bit_line_index + 2], 2 * i);
                }
                if (num & (1 << 3)) {
                    BitSet128_set_1(&Frames[index].lines[bit_line_index + 3], 2 * i);
                }
                if (num & (1 << 4)) {
                    BitSet128_set_1(&Frames[index].lines[bit_line_index + 0], 2 * i + 1);
                }
                if (num & (1 << 5)) {
                    BitSet128_set_1(&Frames[index].lines[bit_line_index + 1], 2 * i + 1);
                }
                if (num & (1 << 6)) {
                    BitSet128_set_1(&Frames[index].lines[bit_line_index + 2], 2 * i + 1);
                }
                if (num & (1 << 7)) {
                    BitSet128_set_1(&Frames[index].lines[bit_line_index + 3], 2 * i + 1);
                }
            }
            bit_line_index += 4;
            continue;
        }
        fprintf(stderr, "Invalid file data, line: %s", line);
        exit(1);
    }

    fclose(frame_file);
    IsInit = true;
}

BadAppleFrame badapple_get(const uint32_t count) {
    if (IsInit == false) {
        perror("You must call `badapple_init()` first.\n");
        exit(1);
    }
    if (count < BADAPPLE_FRAME_COUNT) {
        return Frames[count];
    }
    fprintf(stderr, "Index out of range error: `count` must be lower than %d, but actual %d", BADAPPLE_FRAME_COUNT, count);
    exit(1);
}
