#include <avr/pgmspace.h>

#include <util/delay.h>

#include "device.h"

inline  void show_column(uint8_t column) {
    PORTB = column;
}