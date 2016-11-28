#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <util/delay.h>
#include <avr/io.h>

#include "config.h"
#include "output.h"
#include "font.h"

double DELAY_AFTER_GLYPH_COLUMN_MS;
double DELAY_AFTER_GLYPH_MS;

/**
 * How much time to wait between two columns.
 *
 * The idea is to squeeze the whole message into one sweep.
 *
 * Sweep duration is given by TIME_FOR_ONE_SWEEP_MS
 *
 */
double delayCharColumnMs(uint8_t number_of_glyphs)  {
    return (TIME_FOR_ONE_SWEEP_MS / (number_of_glyphs * (GLYPH_WIDTH + DELAY_AFTER_GLYPH_FACTOR)));
}


/*
* Wait until the stick changes waving direction
*/
void wait_for_reverse_waving_direction() {
    _delay_ms(DELAY_REVERSE_WAVING_MS);
}

void write_string(const char *message, uint8_t message_len) {
    for (uint8_t i = 0; i < message_len; i++) {
        output_char(message[i], DELAY_AFTER_GLYPH_COLUMN_MS);
        _delay_ms(DELAY_AFTER_GLYPH_MS);
    }
}

void write_string_reverse(const char *message, uint8_t message_len) {
    for (uint8_t i = message_len - 1; i > 0; i--) {
        _delay_ms(DELAY_AFTER_GLYPH_MS);
        output_char_rev(message[i], DELAY_AFTER_GLYPH_COLUMN_MS);
    }
}

int main(void) {
    DDRB = 0xFF; // PORTB is output, all pins
    PORTB = 0x00; // Make pins low to start

    const char *message = MESSAGE;
    uint8_t message_len = strlen(message);

    DELAY_AFTER_GLYPH_COLUMN_MS =  delayCharColumnMs(strlen(message));
    DELAY_AFTER_GLYPH_MS = DELAY_AFTER_GLYPH_COLUMN_MS * DELAY_AFTER_GLYPH_FACTOR;

    for (;;) {
        // The PO Vis created by quickly waving the stick left
        // to right and back.

        write_string(message, message_len);
        wait_for_reverse_waving_direction();
        write_string_reverse(message, message_len);
        wait_for_reverse_waving_direction();
    }
    return 0;
}
