#pragma once

/**
 * The message to show
 */
#define MESSAGE "this is a test"

/**
 * How much time to wait between two columns
 *
 * Time per character: DELAY_CHAR_COLUMN_MS * GLYPH_WIDTH + DELAY_AFTER_CHAR_MS
 */
#define DELAY_CHAR_COLUMN_MS 10

#define DELAY_AFTER_CHAR_MS (2*DELAY_CHAR_COLUMN_MS)

/*
 * How much time to give the human to reverse waving direction
 */
#define DELAY_REVERSE_WAVING_MS 30

