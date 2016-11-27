#include <avr/pgmspace.h>
#include "device.h"

void show_column(uint8_t column) {
    PORTB = column;
}

void delay_ms(double ms) {
    _delay_ms(ms);
};

