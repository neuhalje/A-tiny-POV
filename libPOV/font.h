#include <stdbool.h>
#include <stdint.h>


#define GLYPH_WIDTH 5

/*
 columns points to an array with at least 8 free bytes

 return: 
   true: glyph found
   false: glyph not found
*/
bool read_font_char_columns(const char glyph, uint8_t *columns);
