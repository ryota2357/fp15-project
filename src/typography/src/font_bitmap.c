#include "../include/font_bitmap.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/free.h"

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
    char* substr = calloc(dir_length, sizeof(char));  // hoge/fuga/typography/src/ -> hoge/fuga/typography/font-bitmap/resources/chardata.txt
    sprintf(file_name, "%s/font-bitmap/resources/chardata.txt", substring(dir, 0, strlen(dir) - 5, substr, dir_length));
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

// https://programming-place.net/ppp/contents/c/rev_res/array010.html
static int compare_uint32_t(const void* a, const void* b) {
    const uint32_t na = *(uint32_t*)a;
    const uint32_t nb = *(uint32_t*)b;
    return na == nb ? 0 : (na > nb ? 1 : -1);  // because uint32_t, cannot do subtraction.
}

size_t array_unique(uint32_t* array, size_t size) {
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
    char line[TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE * TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE + 10] = {0};
    size_t index = 0;
    CharBitMap save_bitmap[300] = {0};  // now, 289 characters
    while (fgets(line, sizeof(line), chardata_file) != NULL) {
        if (index >= 300) {
            fprintf(stderr, "Internal error: you must expand save_bitmap array size (fix %s:%d)", __FILE__, __LINE__ - 3);
            exit(1);
        }
        if (line[0] == 'c') {
            char byte_len[2] = {0};
            substring(line, 2, 1, byte_len, sizeof(byte_len));
            Char32 current_char = {0};
            substring(line, 3, atoi(byte_len), current_char.chars, sizeof(current_char.chars));
            save_bitmap[index].character = current_char;
            continue;
        }
        if (line[0] == 'b') {
            char bitmap[TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE * TYPOGRAPHY_FONT_BITMAP_PIXEL_SIZE + 1] = {0};
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
        const size_t count = array_unique(bases, size);
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

    fclose(chardata_file);
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
