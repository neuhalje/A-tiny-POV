/*
 * atPOV - ATtiny based Persistence Of View gadget
 *
 * Copyright (C) 2016 Jens Neuhalfen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

/*!
 * \file
 * \ingroup devices
 *
 * \brief Hardware abstractions for \rev libPOV and \ref tests.
 *
 */

#include <stdint.h>
#include "device_specific.h"


/*!
 * \addtogroup devices
 * \{
 */

/*!
 * \brief Output \p column on the LEDs.
 * \param column Bit encoded state of the LEDs (0: off, 1: on).
 *               LEDs are identified LSB (bottom) to MSB (top) of the glyph
 * \return void
 */
void show_column(uint8_t column);



#if !defined(__DOXYGEN__)

static __inline__ void delay_us(uint16_t __us) __attribute__((__always_inline__));

static __inline__ void delay_ms(uint16_t __ms) __attribute__((__always_inline__));

#endif

/**
    \ingroup util_delay

    Perform a busy wait  of \c ms milliseconds.

    The macro F_CPU is supposed to be defined to a
    constant defining the CPU clock frequency (in Hertz).
  */
void
delay_ms(const uint16_t ms) {

    const uint32_t __ticks_dc_per_ms = ((F_CPU) / 1e3);

    extern void __builtin_avr_delay_cycles(unsigned long);

    for (uint16_t bit = 1; bit < 16; bit++) {
        if (ms & (1 << bit)) __builtin_avr_delay_cycles(__ticks_dc_per_ms << bit);
    }
}

/**
    \ingroup util_delay

    Perform a busy wait of \c us microseconds.

    The macro F_CPU is supposed to be defined to a
    constant defining the CPU clock frequency (in Hertz).
  */
void
delay_us(const uint16_t us) {
    const uint32_t __ticks_dc_per_us = ((F_CPU) / 1e6);

    extern void __builtin_avr_delay_cycles(unsigned long);

    for (uint16_t bit = 1; bit < 16; bit++) {
        if (us & (1 << bit)) __builtin_avr_delay_cycles(__ticks_dc_per_us << bit);
    }
}

/*! \} */
