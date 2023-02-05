#include "../include/font_bitmap.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool IsInit = false;

static const uint32_t BasePrimaryCandidate[5] = {104729, 104723, 104717, 104711, 104707};
static uint32_t BasePrimary = 0;
static bool HasBitMap[104729] = {0};
static CharBitMap BitMaps[104729] = {0};  // length = max(BasePrimaryCandidate)

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

static FILE* get_chardata_file(void) {
    char dir[250] = "";
    const char* this_file = __FILE__;
    const int len = strlen(this_file);
    const char* dir_end = strrchr(this_file, '/');
    for (int i = 0; i < len; i++) {
        dir[i] = this_file[i];
        if (this_file + i == dir_end) {
            break;
        }
    }

    char file_name[250];
    char s[250] = "";  // hoge/fuga/typography/src/ -> hoge/fuga/typography/font-bitmap/resources/chardata.txt
    sprintf(file_name, "%s/font-bitmap/resources/chardata.txt", substring(dir, 0, strlen(dir) - 5, s, sizeof(s)));

    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Could not open frames data file: %s\n", file_name);
        exit(1);
    }
    return file;
}

// https://programming-place.net/ppp/contents/c/rev_res/array010.html
static int compare_uint32_t(const void* a, const void* b) {
    uint32_t na = *(uint32_t*)a;
    uint32_t nb = *(uint32_t*)b;
    return na == nb ? 0 : (na > nb ? 1 : -1);  // because uint32_t, cannot do subtraction.
}
size_t array_unuque(uint32_t* array, size_t size) {
    size_t end = 0;
    for (size_t i = 1; i < size; ++i) {
        if (array[i] != array[end]) {
            ++end;
            array[end] = array[i];
        }
    }
    return end + 1;
}

void font_bitmap_init(void) {
    FILE* chardata_file = get_chardata_file();

    // read file
    char line[TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE * TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE + 10];
    size_t index = 0;
    CharBitMap save_bitmap[300];  // now, 255 characters
    while (fgets(line, sizeof(line), chardata_file) != NULL) {
        if (line[0] == 'c') {
            Char32 current_char;
            substring(line, 2, 3, current_char.chars, sizeof(current_char.chars));
            save_bitmap[index].character = current_char;
            continue;
        }
        if (line[0] == 'b') {
            char bitmap[TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE * TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE + 1];
            substring(line, 2, TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE * TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE, bitmap, sizeof(bitmap));
            for (uint16_t i = 0; i < TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE; ++i) {
                save_bitmap[index].bitmap[i] = 0;
                for (uint16_t j = 0; j < TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE; ++j) {
                    char b = bitmap[i * TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE + j];
                    save_bitmap[index].bitmap[i] |= ((uint64_t)(b - '0')) << j;
                }
            }
            index += 1;
            continue;
        }
        fprintf(stderr, "Invalid file data, line: %s", line);
        exit(1);
    }

    // calc BasePrimary
    const size_t size = index;
    for (int i = 0; i < 5; ++i) {  // 5 = the length of BasePrimaryCandidate
        BasePrimary = BasePrimaryCandidate[i];
        uint32_t* bases = calloc(size, sizeof(uint32_t));
        for (size_t j = 0; j < size; ++j) {
            bases[j] = save_bitmap[j].character.code % BasePrimary;
        }
        qsort(bases, size, sizeof(uint32_t), compare_uint32_t);
        const size_t count = array_unuque(bases, size);
        free(bases);
        if (count == size) {
            break;
        } else if (i < 4) {
            continue;
        } else {
            perror("Internal erorr: not found base primary number.\n");
            exit(1);
        }
    }

    // create bitmap
    for (size_t i = 0; i < size; ++i) {
        const uint32_t id = save_bitmap[i].character.code % BasePrimary;
        BitMaps[id] = save_bitmap[i];
        HasBitMap[id] = true;
    }

    IsInit = true;
}

CharBitMap font_bitmap_get(const Char32 ch) {
    if (IsInit == false) {
        perror("You must call `font_bitmap_init()` first.\n");
        exit(1);
    }
    const uint32_t id = ch.code % BasePrimary;
    if (HasBitMap[id]) {
        return BitMaps[id];
    }
    fprintf(stderr, "Not found bitmap, you must register it to charset.txt: `%s`\n", ch.chars);
    exit(1);
}
