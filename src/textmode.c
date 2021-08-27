#include <stdint.h>
#include "config.h"

// #include "tama_mini02_font.h"
#include "font.h"

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8

/*const __flash uint8_t text[] = {
    4, 10, 5, 14, 16, 0,
    7, 14, 13, 16, 17, 15, 18, 7, 17, 11, 14, 13, 16, 0,
    3, 1, 3, 2, 0,
    6, 19, 0,
    4, 14, 15, 8, 9, 12, 11, 17, 7, 10
};*/
const __flash uint8_t text[] = "CHAOS CONSTRUCTIONS 2021 BY COREGLITCH";

static inline void textmode_init() {

}

static inline void render_char(uint8_t x, uint8_t y, uint8_t ch) {
    if(x == CHAR_WIDTH - 1) {
        // pixel_value = 0;
    } else if(y == CHAR_HEIGHT ) {
        // pixel_value = 0;
    } else {
        pixel_value = (font[ch - ' '][x] & (1 << y)) >> y;
    }
}

static inline void textmode_render(uint8_t x, uint8_t y) {
    register uint8_t char_pos_x = x / CHAR_WIDTH;
    register uint8_t ch = text[char_pos_x];
    render_char(x % CHAR_WIDTH, y % CHAR_HEIGHT, ch);
}

static inline void textmode_update(uint16_t t) {

}