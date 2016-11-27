#include <stdint.h>
#include "device_specific.h"

#pragma once

void show_column(uint8_t column) __attribute__((always_inline));

void delay_ms(double ms) __attribute__((always_inline));
