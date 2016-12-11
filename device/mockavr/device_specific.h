#ifndef ATPOV_DEVICE_AVR_H
#define ATPOV_DEVICE_AVR_H

#include <string.h>

/**
 * Contains mocks for builds targeted at the build system (unit tests)
 */

#define F_CPU 1

#define PROGMEM

#define pgm_read_byte(ptr)  (*(ptr))
#define memcpy_P(dst, src, len) memcpy(dst,src,len)

extern uint8_t DDRB;
extern uint8_t PORTB;

#endif //ATPOV_DEVICE_AVR_H
