#include "../include/color.h"

#include <stdint.h>

Color color_new(const uint8_t r, const uint8_t g, const uint8_t b) {
    return (Color){r, g, b};
}
