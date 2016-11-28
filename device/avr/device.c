#include <avr/pgmspace.h>

#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

#include "device.h"

void show_column(uint8_t column) {
    PORTB = column;
}

void delay_ms(double ms) {
    _delay_ms(ms);
};

