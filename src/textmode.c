#include <stdint.h>
#include "config.h"

#include "tama_mini02_font.h"

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8

#define DISPLAY_CHAR_WIDTH DISPLAY_WIDTH / CHAR_WIDTH
#define DISPLAY_CHAR_HEIGHT DISPLAY_HEIGHT / CHAR_HEIGHT

// uint8_t start_text[DISPLAY_CHAR_WIDTH * DISPLAY_CHAR_HEIGHT + 1];
// uint8_t text[DISPLAY_CHAR_WIDTH * DISPLAY_CHAR_HEIGHT + 1];
// uint8_t target_text[DISPLAY_CHAR_WIDTH * DISPLAY_CHAR_HEIGHT + 1] = "WELCOME TO CC !";

// uint8_t text_show_pos = 0;


static inline void textmode_init() {
    /*for(uint8_t i = 0; i < DISPLAY_CHAR_WIDTH * DISPLAY_CHAR_HEIGHT; i++) {
        start_text[i] = target_text[i] - 10;
        text[i] = ' ';
    }

    text[DISPLAY_CHAR_WIDTH * DISPLAY_CHAR_HEIGHT] = '\0';
    start_text[DISPLAY_CHAR_WIDTH * DISPLAY_CHAR_HEIGHT] = '\0';

    text[0] = start_text[0];
    */
}

static inline void render_char(uint8_t x, uint8_t y, uint8_t ch) {
    
    if(x == CHAR_WIDTH - 1) {
        // pixel_value = 0;
    } else if(y == CHAR_HEIGHT - 1) {
        // pixel_value = 0;
    } else {
        pixel_value = (font[ch][x] & (1 << y)) >> y;
    }
}

static inline void textmode_render(uint8_t x, uint8_t y) {
    /*uint8_t char_pos_x = x / CHAR_WIDTH;
    uint8_t char_pos_y = y / CHAR_HEIGHT;

    uint8_t ch = text[char_pos_y * DISPLAY_CHAR_WIDTH + char_pos_x];*/

    // render_char(x % CHAR_WIDTH, y % CHAR_HEIGHT, 1);
    render_char(x, y % CHAR_HEIGHT, 1);
}

static inline void textmode_update(uint16_t t) {
    /*if(target_text[text_show_pos] == 0) {
        return;
    }

    if(t % 2 == 0) {
        text[text_show_pos]++;

        if(text[text_show_pos] == target_text[text_show_pos]) {
            text_show_pos++;
            text[text_show_pos] = start_text[text_show_pos];
        }
    }*/
}