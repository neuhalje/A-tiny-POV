#pragma once

/**
 * How long does one sweep (left to right) take?
 *
 * It should take less than 50ms for the POV effect to work.
 */
#define TIME_FOR_ONE_SWEEP_MS 50.0

/**
 * The message to show
 */
#define MESSAGE "hello"

/**
 * How large is the letter spacing column after a glyph.
 *
 * Unit: times 'a column of a glyph'
 *
 * E.g. 1.2 --> Letter spacing is 1.2 as wide as a column in a glyph
 */
#define DELAY_AFTER_GLYPH_FACTOR 1.2


/*
 * How much time to give the human to reverse waving direction
 */
#define DELAY_REVERSE_WAVING_MS 2

