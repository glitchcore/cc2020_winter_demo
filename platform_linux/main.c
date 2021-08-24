#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define clear() printf("\033[H\033[J")

#define REG_8(NAME,REG) uint8_t NAME
#define NOINIT
#define __flash

#include "demo.c"

int main(int argc, char const *argv[])
{
    init_render();
    printf("hello\n");

    while(1) {
        for(size_t y = 0; y < DISPLAY_HEIGHT; y++) {
            for(size_t x = 0; x < DISPLAY_WIDTH; x++) {
                handle_tick();

                if(pixel_value == 1) {
                    printf("*");
                } else if(pixel_value > 1){
                    printf("%c", pixel_value);
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