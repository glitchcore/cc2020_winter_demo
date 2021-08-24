#include "config.h"

/* modes */
typedef enum {
    ModeZebra,
    ModeText,
    ModePoint,
} Mode;

/* zebra mode */

#define ZEBRA_PERIOD 3000
#define ZEBRA_LENGTH 6

/* text mode */

uint8_t textmode_render(uint8_t x, uint8_t y);
void textmode_update(uint32_t t);
void textmode_init();

/* common */

REG_8(column_counter, "r3");
REG_8(row_counter, "r4");
REG_8(t, "r5");
REG_8(pixel_value, "r6");
REG_8(mode, "r7");
REG_8(zebra_phase, "r8");
REG_8(zebra_t, "r9");
NOINIT uint16_t num_pixel;

static inline void init_render() {
    column_counter = 0;
    row_counter = 0;
    t = 0;
    pixel_value = 0;
    mode = ModePoint;
    zebra_phase = 0;
    zebra_t = 0;
    num_pixel = 0;
}

static inline void render_pixel(uint16_t t, uint8_t x, uint8_t y) {
    switch(mode) {
        case ModeZebra:
            if((x + zebra_phase) % ZEBRA_LENGTH == 0) {
                pixel_value = 1;
            } else {
                pixel_value = 0;
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
                pixel_value = 1;
            } else {
                pixel_value = 0;
            }
        break;

        default:
            pixel_value = 0;
        break;
    }
}

static inline void render_row(uint16_t t, uint8_t y) {

}

static inline void render_frame(uint16_t t) {
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

static inline void handle_tick() {
    pixel_value = 0;

#ifdef FLIP_DISPLAY
    render_pixel(t, DISPLAY_WIDTH - column_counter - 1, row_counter);
#else
    render_pixel(t, column_counter, row_counter);
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
}
