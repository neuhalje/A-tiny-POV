#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <util/delay.h>
#include <avr/io.h>

#include "config.h"
#include "output.h"

/*
* Wait until the stick changes waving direction
*/
void wait_for_reverse_waving_direction() {
    _delay_ms(DELAY_REVERSE_WAVING_MS);
}

void write_string(const char *message, uint8_t message_len) {
    for (uint8_t i = 0; i < message_len; i++) {
        output_char(message[i]);
    }
}

void write_string_reverse(const char *message, uint8_t message_len) {
    for (uint8_t i = message_len - 1; i > 0; i--) {
        output_char_rev(message[i]);
    }
}

int main(void) {
    DDRB = 0xFF; // PORTB is output, all pins
    PORTB = 0x00; // Make pins low to start

    const char *message = "this is a test";
    uint8_t message_len = strlen(message);


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
