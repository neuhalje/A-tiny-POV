#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <avr/io.h>

#include "device.h"

#include "config.h"
#include "display.h"
#include "font.h"

Font gFont;
Device gDevice;
Display gDisplay(gDevice, gFont);

/**
 * \brief How much time to wait between two columns.
 *
 * The idea is to squeeze the whole message into one sweep.
 *
 * Sweep duration is given by TIME_FOR_ONE_SWEEP_MS
 *
 */
#define WAIT_BETWEEN_COLUMNS_US(number_of_glyphs) ((1000.0 * TIME_FOR_ONE_SWEEP_MS / (number_of_glyphs * (gFont.glyph_width() + DELAY_AFTER_GLYPH_FACTOR))))

#define DELAY_AFTER_GLYPH_COLUMN_US  WAIT_BETWEEN_COLUMNS_US(MESSAGE_LEN)
#define DELAY_AFTER_GLYPH_US  (DELAY_AFTER_GLYPH_COLUMN_US * DELAY_AFTER_GLYPH_FACTOR)

/**
 * Empty column shown after a glyph (space between two glyphs)
 */
static const uint8_t COLUMN_AFTER_GLYPH = 0;



/*
* Wait until the stick changes waving direction
*/
void wait_for_reverse_waving_direction() {
    gDevice.delay_us(1000 * DELAY_REVERSE_WAVING_MS);
}

void write_string(const char *message, uint8_t message_len) {
    for (uint8_t i = 0; i < message_len; i++) {
        gDisplay.output_char(message[i], DELAY_AFTER_GLYPH_COLUMN_US);
        gDevice.show_column(COLUMN_AFTER_GLYPH);
        gDevice.delay_us(DELAY_AFTER_GLYPH_US);
    }
}

void write_string_reverse(const char *message, uint8_t message_len) {
    for (uint8_t i = message_len - 1; i > 0; i--) {
        gDevice.show_column(COLUMN_AFTER_GLYPH);
        gDevice.delay_us(DELAY_AFTER_GLYPH_US);
        gDisplay.output_char_rev(message[i], DELAY_AFTER_GLYPH_COLUMN_US);
    }
}

int main(void) {
    DDRB = 0xFF; // PORTB is output, all pins
    PORTB = 0x00; // Make pins low to start

    const char *message = MESSAGE;
    for (;;) {
        // The PO Vis created by quickly waving the stick left
        // to right and back.

        write_string(message, MESSAGE_LEN);
        wait_for_reverse_waving_direction();
        write_string_reverse(message, MESSAGE_LEN);
        wait_for_reverse_waving_direction();
    }
}
