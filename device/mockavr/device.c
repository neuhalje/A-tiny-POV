#include <stdio.h>
#include "device.h"

void show_column(uint8_t column) {
    printf("Column: %x\n", column);
}

void delay_ms(double ms) {
    // _delay_ms(ms);
};

#define PROGMEM