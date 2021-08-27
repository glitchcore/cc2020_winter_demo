#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#define F_CPU 9600000UL
#include <avr/interrupt.h>

#define REG_8(NAME,REG) volatile register uint8_t NAME asm(REG)
#define NOINIT __attribute__ ((section (".noinit")))

#include "demo.c"

#define WHITE (1<<PB3)

ISR(TIM0_COMPA_vect) {
    TCNT0 = 0;
    handle_tick();
    PORTB = (pixel_value & 0x01) << PB3;
}

__attribute__ ((OS_main)) void main() {
    cli();

    // set PB3 to be output
    DDRB = WHITE;

    OCR0A = 86;
    TCNT0 = 0;

    // set prescaler to 8 (586 Hz)
    TCCR0B = (0 << CS02) | (1 << CS01) | (0 << CS00);

    // enable Timer Overflow irq
    TIMSK0 = (1 << OCIE0A);

    init_render();

    sei();

    while (1) {}
}