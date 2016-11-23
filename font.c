#include "font.c"
#include <avr/pgmspace.h>

typedef struct { 
   const char glyph;
   uint8_t columns[8];
} FontCharacter;

/*
 Font borrowed from http://www.instructables.com/id/10-ATtiny8545-POV-display-works-really-well/?ALLSTEPS
*/
const uint8_t chars_in_font = 30;
const FontCharacter font[chars_in_font] PROGMEM = {
	{ ' ', {0, 0, 0, 0, 0}},
	{ '!', {0, 29, 0, 0, 0}},
	{ '.', {0, 1, 0, 0, 0}},
	{ '?', {8, 19, 20, 8, 0}},
	{ 'a', {1, 6, 26, 6, 1}},
	{ 'b', {31, 21, 21, 10, 0}},
	{ 'c', {14, 17, 17, 10, 0}},
	{ 'd', {31, 17, 17, 14, 0}},
	{ 'e', {31, 21, 21, 17, 0}},
	{ 'f', {31, 20, 20, 16, 0}},
	{ 'g', {14, 17, 19, 10, 0}},
	{ 'h', {31, 4, 4, 4, 31}},
	{ 'i', {0, 17, 31, 17, 0}},
	{ 'j', {0, 17, 30, 16, 0}},
	{ 'k', {31, 4, 10, 17, 0}},
	{ 'l', {31, 1, 1, 1, 0}},
	{ 'm', {31, 12, 3, 12, 31}},
	{ 'n', {31, 12, 3, 31, 0}},
	{ 'o', {14, 17, 17, 14, 0}},
	{ 'p', {31, 20, 20, 8, 0}},
	{ 'q', {14, 17, 19, 14, 2}},
	{ 'r', {31, 20, 22, 9, 0}},
	{ 's', {8, 21, 21, 2, 0}},
	{ 't', {16, 16, 31, 16, 16}},
	{ 'u', {30, 1, 1, 30, 0}},
	{ 'v', {24, 6, 1, 6, 24}},
	{ 'w', {28, 3, 12, 3, 28}},
	{ 'x', {17, 10, 4, 10, 17}},
	{ 'y', {17, 10, 4, 8, 16}},
	{ 'z', {19, 21, 21, 25, 0}},
};

uint8_t font_char_columns(const char glyph, uint8_t * columns);
   if ( column >= 8 ) {
      return 0;
   };

   for (uint8_t glyph_index = 0; glyph_index < chars_in_font; glyph_index++) {
      if (pgm_read_byte( & (font[glyph_index].glyph)) == glyph ) {
          return  memcpy_P (columns, &font[glyph_index].columns[0], 8);
      };
   }
   return 0;
}



