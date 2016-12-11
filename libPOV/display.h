#include "device.h"
#include "font.h"
#include "BU4094BC.h"

class Display {

public:
    Display(Device &device, Font &font, BU4094BC& output) : _device(device), _font(font), _output(output) {};

    /*!
    * \brief Print character \ref c to output 'from left to right'
    */
    void output_char(const char c, const uint16_t delay_after_glyph_column_us);

    /*!
    * \brief Print character \ref c to output 'from right to left'
    */
    void output_char_rev(const char c, const uint16_t delay_after_glyph_column_us);

private:
    Device &_device;
    Font &_font;
    BU4094BC &_output;
};