#ifndef ATPOV_DEVICE_AVR_H
#define ATPOV_DEVICE_AVR_H

#include <string.h>

/**
 * Contains mocks for builds targeted at the build system (unit tests)
 */

#define PROGMEM

#define pgm_read_byte(ptr)  (*(ptr))
#define memcpy_P(dst, src, len) memcpy(dst,src,len)


#endif //ATPOV_DEVICE_AVR_H
