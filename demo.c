#include <stdint.h>
#include "config.h"

#include <stdio.h>

uint8_t column_counter = 0;
uint8_t row_counter = 0;

uint8_t zebra_phase = 0;
uint32_t zebra_t = 0;

#define ZEBRA_PERIOD 3000
#define ZEBRA_LENGTH 6

uint32_t t = 0;

void init_render() {

}


uint8_t render_pixel() {
    t++;

    column_counter++;

    if(column_counter == DISPLAY_WIDTH) {
        column_counter = 0;
        row_counter++;
    }

    if(row_counter == DISPLAY_HEIGHT) {
        row_counter = 0;

        if(t > zebra_t + ZEBRA_PERIOD) {
            zebra_t = t;

            zebra_phase++;
            if(zebra_phase == ZEBRA_LENGTH + 1) {
                zebra_phase = 1;
            }
        }
    }

    // printf("%d\n", zebra_phase);

    if((column_counter + zebra_phase) % ZEBRA_LENGTH == 0) {
        return 1;
    } else {
        return 0;
    }

    return 1;
}