#include <stdbool.h>
#include <stdint.h>


#pragma once

class Font {

public:
    /*!
     * \brief glyph width in pixels
     *
     * @return
     */
    virtual uint8_t glyph_width() const;

    /*!
     \brief read a \ref  glyph into \ref columns

     \param glyph ascii code of the glyph to read
     \param out: columns points to an array with at least 8 free bytes.

    @return
       true: glyph found
       false: glyph not found; *columns is filled with a default glyph
    */
    bool read_font_char_columns(const char glyph, uint8_t *columns);

    virtual ~Font(){};
};