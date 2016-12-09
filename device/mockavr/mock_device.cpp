#include <stdio.h>
#include "device.h"

void Device::show_column(uint8_t column) {
    printf("Column: %x\n", column);
}


void Device::delay_ms(const uint16_t ms) {
    // NOOP
}

void Device::delay_us(const uint16_t us) {
   // NOOP
}