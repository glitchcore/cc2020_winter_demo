#include <stdint.h>
#include "config.h"

#include <stdio.h>

/* modes */
#define ModeZebra 0
#define ModeText 1

uint8_t mode = ModeZebra;

/* zebra mode */

#define ZEBRA_PERIOD 3000
#define ZEBRA_LENGTH 6

uint8_t zebra_phase = 0;
uint8_t zebra_t = 0;

/* text mode */

uint8_t textmode_render(uint8_t x, uint8_t y);
void textmode_update(uint32_t t);
void textmode_init();

/* common */

void init_render() {
    mode = ModeZebra;

    textmode_init();
}

uint8_t render_pixel(uint32_t t, uint8_t column_counter, uint8_t row_counter) {
    /*
    switch(mode) {
        case ModeZebra:
            if((column_counter + zebra_phase) % ZEBRA_LENGTH == 0) {
                return 0;
            } else {
                return 0;
            }
        break;

        case ModeText:
            return textmode_render(column_counter, row_counter);
        break;

        default:
            return 1;
        break;
    }
    */

    return mode;
}

void render_row(uint32_t t, uint8_t row_counter) {

}

void render_frame(uint32_t t) {
    switch(mode) {
        case ModeZebra:
            if(t > zebra_t + ZEBRA_PERIOD) {
                zebra_t = t;

                zebra_phase++;
                if(zebra_phase == ZEBRA_LENGTH + 1) {
                    zebra_phase = 1;
                }
            }
        break;

        case ModeText:
            textmode_update(t);
        break;

        default:
        break;
    }

    /*
    if(t > 50000) {
        mode = ModeZebra;
    }
    */
}

uint8_t handle_tick() {
    static uint8_t column_counter = 0;
    static uint8_t row_counter = 0;

    static uint32_t t = 0;

    uint8_t res = render_pixel(t, column_counter, row_counter);

    /*
    t++;

    column_counter++;

    if(column_counter == DISPLAY_WIDTH) {
        render_row(t, row_counter);

        column_counter = 0;
        row_counter++;
    }

    if(row_counter == DISPLAY_HEIGHT) {
        render_frame(t);

        row_counter = 0;
    }
    */

    return mode;
}