#include <stdbool.h>
#include <stdint.h>


#pragma once

/*!
 * \brief Implementation of the font used.
 *
 * Font data is stored in program space to conserve RAM.
 */
class Font {

public:
    Font() = default;
    Font(Font&&) = default;

    // prevent calls to unwanted generated functions
    Font(const Font&) = delete;
    Font& operator= (const Font&) = delete;

    /*!
     * \brief glyph width (and height) in pixels.
     *
     * @return width
     */
    uint8_t glyph_width() const;

    /*!
     \brief read a \ref glyph into \ref columns .

     \param glyph   - ascii code of the glyph to read.
     \param columns - columns points to an array with at least 8 free bytes.

    @return
       true: glyph found
       false: glyph not found; *columns is filled with a default glyph
    */
    bool read_font_char_columns(const char glyph, uint8_t *columns);

     // AVR does not support new and delete
     // http://www.avrfreaks.net/forum/c-new-delete-operator-confusion?name=PNphpBB2&file=viewtopic&t=44295
     // Not implementing this will make the test compile complain about non-virtual destructor.
     // This is fine, since the one instance is never deleted on the AVR
     // ~Font()  = delete;
};