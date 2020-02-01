#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "config.h"

#define clear() printf("\033[H\033[J")

uint8_t handle_tick();
void init_render();

int main(int argc, char const *argv[])
{
    init_render();
    printf("hello\n");

    while(1) {
        for(size_t y = 0; y < DISPLAY_HEIGHT; y++) {
            for(size_t x = 0; x < DISPLAY_WIDTH; x++) {
                uint8_t ch = handle_tick();

                if(ch == 1) {
                    printf("*");
                } else if(ch > 1){
                    printf("%c", ch);
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