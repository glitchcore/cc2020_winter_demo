#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t handle_tick();
void init_render();

ISR(TIMER0_COMPA_vect) {
    if(handle_tick() > 0) {
        PORTB = 0b00000010;
    } else {
        PORTB = 0b00000000;
    }

    // PORTB ^= 0b00000010;
}

int main() {
    init_render();

    // set PB1 to be output
    DDRB = 0b00000010;

    TCCR0A = (1 << WGM01); //CTC mode
    TCCR0B = (2 << CS00);  //div8
    OCR0A = 16000000/8 * 0.000061 - 1; // 50us compare value
    TIMSK |= (1<<OCIE0A); // if you want interrupt

    sei();

    while (1) {
        _delay_ms(10);
    }

    return 1;
}