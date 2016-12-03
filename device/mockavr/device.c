#include <stdio.h>
#include "device.h"

void show_column(uint8_t column) {
    printf("Column: %x\n", column);
}


/**
 * NOOP Implementation for local compilation.
 */
void __builtin_avr_delay_cycles(unsigned long dummy) {};
