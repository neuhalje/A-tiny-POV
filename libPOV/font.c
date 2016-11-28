#include <stdbool.h>
#include <stddef.h>
#include "font.h"
#include "device.h"

typedef struct {
    const char glyph;
    uint8_t columns[GLYPH_WIDTH];
} FontCharacter;

/*
 Font borrowed from http://www.instructables.com/id/10-ATtiny8545-POV-display-works-really-well/
*/
#define CHARS_IN_FONT  33
#define DEFAULT_GLYPH_INDEX  32
const FontCharacter font[CHARS_IN_FONT] PROGMEM = {
        {.glyph = ' ', .columns = {0, 0, 0, 0, 0}},
        {.glyph = '/', .columns = {1, 2, 4, 8, 16}},
        {.glyph = '\\', .columns = {16, 8, 4, 2, 1}},
        {.glyph ='!', .columns =  {0, 29, 0, 0, 0}},
        {.glyph ='.', .columns =  {0, 1, 0, 0, 0}},
        {.glyph ='?', .columns =  {8, 19, 20, 8, 0}},
        {.glyph ='a', .columns =  {1, 6, 26, 6, 1}},
        {.glyph ='b', .columns =  {31, 21, 21, 10, 0}},
        {.glyph ='c', .columns =  {14, 17, 17, 10, 0}},
        {.glyph ='d', .columns =  {31, 17, 17, 14, 0}},
        {.glyph ='e', .columns =  {31, 21, 21, 17, 0}},
        {.glyph ='f', .columns =  {31, 20, 20, 16, 0}},
        {.glyph ='g', .columns =  {14, 17, 19, 10, 0}},
        {.glyph ='h', .columns =  {31, 4, 4, 4, 31}},
        {.glyph ='i', .columns =  {0, 17, 31, 17, 0}},
        {.glyph ='j', .columns =  {0, 17, 30, 16, 0}},
        {.glyph ='k', .columns =  {31, 4, 10, 17, 0}},
        {.glyph ='l', .columns =  {31, 1, 1, 1, 0}},
        {.glyph ='m', .columns =  {31, 12, 3, 12, 31}},
        {.glyph ='n', .columns =  {31, 12, 3, 31, 0}},
        {.glyph ='o', .columns =  {14, 17, 17, 14, 0}},
        {.glyph ='p', .columns =  {31, 20, 20, 8, 0}},
        {.glyph ='q', .columns =  {14, 17, 19, 14, 2}},
        {.glyph ='r', .columns =  {31, 20, 22, 9, 0}},
        {.glyph ='s', .columns =  {8, 21, 21, 2, 0}},
        {.glyph ='t', .columns =  {16, 16, 31, 16, 16}},
        {.glyph ='u', .columns =  {30, 1, 1, 30, 0}},
        {.glyph ='v', .columns =  {24, 6, 1, 6, 24}},
        {.glyph ='w', .columns =  {28, 3, 12, 3, 28}},
        {.glyph ='x', .columns =  {17, 10, 4, 10, 17}},
        {.glyph ='y', .columns =  {17, 10, 4, 8, 16}},
        {.glyph ='z', .columns =  {19, 21, 21, 25, 0}},
        {.glyph ='#', .columns =  {0xff, 0xff, 0xff, 0xff, 0xff}},
};

/*
 Implementation detail: We are actually scanning the whole array.

 Binary search might be faster, but we are talking about
 lg_2(CHARS_IN_FONT) vs. CHARS_IN_FONT/2  (5 vs 16) comparisons.
*/
bool read_font_char_columns(const char glyph, uint8_t *dst_columns) {
    if (dst_columns == NULL) { return false; }

    for (uint8_t glyph_index = 0; glyph_index < CHARS_IN_FONT; glyph_index++) {
        if (pgm_read_byte(&(font[glyph_index].glyph)) == glyph) {
            memcpy_P (dst_columns, &font[glyph_index].columns[0], GLYPH_WIDTH);
            return true;
        };
    }

    memcpy_P(dst_columns, &font[DEFAULT_GLYPH_INDEX].columns[0], GLYPH_WIDTH);
    return false;
}



