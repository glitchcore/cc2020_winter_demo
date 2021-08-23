#include <stdbool.h>
#include <avr/io.h>

#define F_CPU 9600000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define WHITE (1<<PB3)
 
uint8_t handle_tick();

ISR(TIM0_COMPA_vect) {
    TCNT0 = 0;

    PORTB = (handle_tick() & 0x1) << PB3;
}

int main() {
    cli();

    // set PB3 to be output
    DDRB = WHITE;

    OCR0A = 94;
    TCNT0 = 0;

    // set prescaler to 8 (586 Hz)
    TCCR0B = (0 << CS02) | (1 << CS01) | (0 << CS00);

    // enable Timer Overflow irq
    TIMSK0 = (1 << OCIE0A);

    sei();

    while (1) {
        // PORTB |= WHITE;
        // _delay_ms(250);
        // set PB3 low
        // PORTB &= ~WHITE;
        // _delay_ms(250);
    }

    return 1;
}