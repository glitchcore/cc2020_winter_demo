#include <stdint.h>
#include "config.h"

#include <stdio.h>

/* modes */
typedef enum {
    ModeZebra
} Mode;

Mode mode = ModeZebra;

/* zebra mode */

#define ZEBRA_PERIOD 3000
#define ZEBRA_LENGTH 6

uint8_t zebra_phase = 0;
uint32_t zebra_t = 0;

void init_render() {

}

uint8_t render_pixel(uint32_t t, uint8_t column_counter, uint8_t row_counter) {
    switch(mode) {
        case ModeZebra:
            if((column_counter + zebra_phase) % ZEBRA_LENGTH == 0) {
                return 1;
            } else {
                return 0;
            }
        break;

        default:
        break;
    }
}

void render_row(uint32_t t, uint8_t row_counter) {

}

void render_frame(uint32_t t) {
    if(t > zebra_t + ZEBRA_PERIOD) {
        zebra_t = t;

        zebra_phase++;
        if(zebra_phase == ZEBRA_LENGTH + 1) {
            zebra_phase = 1;
        }
    }
}

uint8_t handle_tick() {
    static uint8_t column_counter = 0;
    static uint8_t row_counter = 0;

    static uint32_t t = 0;

    t++;

    column_counter++;

    if(column_counter == DISPLAY_WIDTH) {
        column_counter = 0;
        row_counter++;

        render_row(t, row_counter);
    }

    if(row_counter == DISPLAY_HEIGHT) {
        row_counter = 0;

        render_frame(t);
    }

    return render_pixel(t, column_counter, row_counter);
}