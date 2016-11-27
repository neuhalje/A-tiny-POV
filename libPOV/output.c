#include "device.h"
#include "output.h"
#include "font.h"
#include "config.h"

/*
* Print character 'c' to output 'from left to right'
*/
void output_char(const char c) {
    uint8_t columns[GLYPH_WIDTH];
    read_font_char_columns(c, columns);

    for (uint8_t column = 0; column < GLYPH_WIDTH; column++) {
        show_column(columns[column]);
        delay_ms(DELAY_CHAR_COLUMN_MS);
    }
}

/*
* Print character 'c' to output 'from right to left'
*/
void output_char_rev(const char c) {
    uint8_t columns[GLYPH_WIDTH];
    read_font_char_columns(c, columns);

    for (uint8_t column = GLYPH_WIDTH - 1; column > 0; column--) {
        show_column(columns[column]);
        delay_ms(DELAY_CHAR_COLUMN_MS);
    }
}
