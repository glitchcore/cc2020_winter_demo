#include "config.h"

/* modes */
typedef enum {
    ModeZebra,
    ModeText,
    ModePoint,
} Mode;

/* zebra mode */

#define ZEBRA_PERIOD 2
#define ZEBRA_LENGTH 8

#define ZEBRA_TIME 24 * 10
#define TEXT_TIME 24 * 16

/* common */

REG_8(column_counter, "r3");
REG_8(row_counter, "r4");
NOINIT uint16_t t;
REG_8(pixel_value, "r6");
REG_8(mode, "r7");
REG_8(zebra_phase, "r8");
NOINIT uint16_t zebra_t;
NOINIT uint16_t num_pixel;

#include "textmode.c"

static inline void init_render() {
    column_counter = 0;
    row_counter = 0;
    t = 0;
    pixel_value = 0;
    mode = ModePoint;
    zebra_phase = 0;
    zebra_t = 0;

    num_pixel = DISPLAY_WIDTH;

    textmode_init();
}

static inline void render_zebra(uint16_t t, uint8_t x, uint8_t y) {
    if((x + zebra_phase) % ZEBRA_LENGTH < 4) {
        pixel_value = 1;
    } else {
        // pixel_value = 0;
    }
}

static inline void render_pixel(uint16_t t, uint8_t x, uint8_t y) {
    switch(mode) {
        case ModeZebra:
            render_zebra(t, x, y);
        break;

        case ModeText:
            if(y > 3 && y < CHAR_HEIGHT + 5) {
                textmode_render(x + (t - TEXT_TIME) / 2 - 30, y - 5);
            } else {
                render_zebra(t, x, y);
            }
        break;

        case ModePoint:
            if(
                x == 0 || y == 0 ||
                x == (DISPLAY_WIDTH - 1) || y == (DISPLAY_HEIGHT - 1) ||
                (x + y * DISPLAY_WIDTH) < num_pixel
            ) {
                pixel_value = 1;
            } else {
                // pixel_value = 0;
            }
        break;

        default:
            // pixel_value = 0;
        break;
    }
}

static inline void render_row(uint16_t t, uint8_t y) {

}

static inline void render_frame(uint16_t t) {
    if(t > zebra_t + ZEBRA_PERIOD) {
        zebra_t = t;

        zebra_phase++;
        if(zebra_phase == ZEBRA_LENGTH + 1) {
            zebra_phase = 1;
        }
    }

    switch(mode) {
        case ModeText:
            textmode_update(t);
        break;

        case ModePoint:
            num_pixel += 2;
            if(num_pixel == DISPLAY_WIDTH * DISPLAY_HEIGHT) {
                num_pixel = 0;
            }
        default:
        break;
    }

    // scene sequencer
#if 1
    if(t > TEXT_TIME) {
        mode = ModeText;
    } else if(t > ZEBRA_TIME) {
        mode = ModeZebra;
    } else {
        mode = ModePoint;
    }
#else
    mode = ModeText;
#endif
}

static inline void handle_tick() {
    pixel_value = 0;

#ifdef FLIP_DISPLAY
    render_pixel(t, DISPLAY_WIDTH - column_counter - 1, row_counter);
#else
    render_pixel(t, column_counter, row_counter);
#endif

    column_counter++;

    if(column_counter == DISPLAY_WIDTH) {
        render_row(t, row_counter);

        column_counter = 0;
        row_counter++;
    }

    if(row_counter == DISPLAY_HEIGHT) {
        t++;
        render_frame(t);

        row_counter = 0;
    }
}
