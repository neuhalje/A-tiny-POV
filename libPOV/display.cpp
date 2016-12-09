#include "device.h"
#include "display.h"
#include "font.h"
#include "config.h"


void Display::output_char(const char c, const uint16_t delay_after_glyph_column_us) {
    uint8_t columns[_font.glyph_width()];
    _font.read_font_char_columns(c, columns);

    for (uint8_t column = 0; column < _font.glyph_width(); column++) {
        _device.show_column(columns[column]);
        _device.delay_us(delay_after_glyph_column_us);
    }
}


void Display::output_char_rev(const char c, const uint16_t delay_after_glyph_column_us) {
    uint8_t columns[_font.glyph_width()];
    _font.read_font_char_columns(c, columns);

    for (uint8_t column = _font.glyph_width() - 1; column > 0; column--) {
        _device.show_column(columns[column]);
        _device.delay_us(delay_after_glyph_column_us);
    }
}
