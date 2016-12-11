#include <avr/pgmspace.h>

#include <util/delay.h>

#include "device.h"

void Device::show_column(uint8_t column) {
    PORTB = column;
}

void Device::delay_ms(const uint16_t ms) {

    const uint32_t __ticks_dc_per_ms = ((F_CPU) / 1e3);

    extern void __builtin_avr_delay_cycles(unsigned long);

    for (uint16_t bit = 1; bit < 16; bit++) {
        // __builtin_avr_delay_cycles can only be called with
        // parameters that are known at compile time
        // E.g. __builtin_avr_delay_cycles(__ticks_dc_per_ms * ms) does not work.
        //
        // This implementation replaces '__ticks_dc_per_ms * ms' with
        // bit shifts.
        if (ms & (1 << bit)) __builtin_avr_delay_cycles(__ticks_dc_per_ms << bit);
    }
}

void Device::delay_us(const uint16_t us) {
    const uint32_t __ticks_dc_per_us = ((F_CPU) / 1e6);

    extern void __builtin_avr_delay_cycles(unsigned long);

    for (uint16_t bit = 1; bit < 16; bit++) {
        // __builtin_avr_delay_cycles can only be called with
        // parameters that are known at compile time
        // E.g. __builtin_avr_delay_cycles(__ticks_dc_per_ms * ms) does not work.
        //
        // This implementation replaces '__ticks_dc_per_ms * ms' with
        // bit shifts.
        if (us & (1 << bit)) __builtin_avr_delay_cycles(__ticks_dc_per_us << bit);
    }
}