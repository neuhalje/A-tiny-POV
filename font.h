/*
 columns points to an array with at least 8 free bytes

 return: 
   true: glyph found
   false: glyph not found
*/
bool font_char_columns(const char glyph, uint8_t * columns);
