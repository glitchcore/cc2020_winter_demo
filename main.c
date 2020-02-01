#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "config.h"

#define clear() printf("\033[H\033[J")

uint8_t render_pixel();
void init_render();

int main(int argc, char const *argv[])
{
    init_render();
    printf("hello\n");

    while(1) {
        for(size_t y = 0; y < DISPLAY_HEIGHT; y++) {
            for(size_t x = 0; x < DISPLAY_WIDTH; x++) {
                if(render_pixel) {
                    printf("*");
                } else {
                    printf(" ");
                }
                printf(" ");
            }
            printf("\n");
        }

        usleep(PIXEL_PERIOD * DISPLAY_WIDTH * DISPLAY_HEIGHT);
        clear();
    }

    return 0;
}