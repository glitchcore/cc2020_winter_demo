#include <stdint.h>
#include "config.h"

#include <stdio.h>

/* modes */
typedef enum {
    ModeZebra,
    ModeText,
    ModePoint,
} Mode;

Mode mode = ModePoint;
uint16_t num_pixel = 0;

/* zebra mode */

#define ZEBRA_PERIOD 3000
#define ZEBRA_LENGTH 6

uint8_t zebra_phase = 0;
uint32_t zebra_t = 0;

/* text mode */

uint8_t textmode_render(uint8_t x, uint8_t y);
void textmode_update(uint32_t t);
void textmode_init();

/* common */

void init_render() {
    // textmode_init();
}

uint8_t render_pixel(uint32_t t, uint8_t x, uint8_t y) {
    switch(mode) {
        case ModeZebra:
            if((x + zebra_phase) % ZEBRA_LENGTH == 0) {
                return 1;
            } else {
                return 0;
            }
        break;

        /*case ModeText:
            return textmode_render(x, y);
        break;*/

        case ModePoint:
            if(
                x == 0 || y == 0 ||
                x == (DISPLAY_WIDTH - 1) || y == (DISPLAY_HEIGHT - 1) ||
                (x + y * DISPLAY_WIDTH) == num_pixel
            ) {
                return 1;
            } else {
                return 0;
            }
        break;

        default:
        break;
    }

    return 0;
}

void render_row(uint32_t t, uint8_t y) {

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

        /*case ModeText:
            textmode_update(t);
        break;*/

        case ModePoint:
            num_pixel++;
            if(num_pixel == DISPLAY_WIDTH * DISPLAY_HEIGHT) {
                num_pixel = 0;
            }

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

#ifdef FLIP_DISPLAY
    uint8_t res = render_pixel(t, DISPLAY_WIDTH - column_counter - 1, row_counter);
#else
    uint8_t res = render_pixel(t, column_counter, row_counter);
#endif

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

    return res;
}