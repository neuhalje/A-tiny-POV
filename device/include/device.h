/*
 * atPOV - ATtiny based Persistence Of Vision gadget
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
 * \ingroup device
 *
 * \brief Hardware abstractions for \ref libPOV and \ref libPOV_tests.
 *
 */

#include <stdint.h>
#include "device_specific.h"

class Device {

public:

    /*!
    *  \interface device_interface
     * \addtogroup device
     * \{
     */

    /*!
     * \brief Output \p column on the LEDs.
     * \param column Bit encoded state of the LEDs (0: off, 1: on).
     *               LEDs are counted from the bottom (LSB) to
     *               the top (MSB) of the glyph.
     * \return void
     */
    void show_column(uint8_t column);


    /*!
    * \brief Perform a busy wait  of \c ms milliseconds.
    * \param ms Number of milliseconds to wait
    *
    * The macro F_CPU is supposed to be defined to a
    * constant defining the CPU clock frequency (in Hertz).
    */
    void delay_ms(const uint16_t ms) {

        const uint32_t __ticks_dc_per_ms = ((F_CPU) / 1e3);

        extern void __builtin_avr_delay_cycles(unsigned long);

        for (uint16_t bit = 1; bit < 16; bit++) {
            if (ms & (1 << bit)) __builtin_avr_delay_cycles(__ticks_dc_per_ms << bit);
        }
    }

    /*!
    * \brief Perform a busy wait of \c us microseconds.
    *
    *  The macro F_CPU is supposed to be defined to a
    *  constant defining the CPU clock frequency (in Hertz).
    */
    void delay_us(const uint16_t us) {
        const uint32_t __ticks_dc_per_us = ((F_CPU) / 1e6);

        extern void __builtin_avr_delay_cycles(unsigned long);

        for (uint16_t bit = 1; bit < 16; bit++) {
            if (us & (1 << bit)) __builtin_avr_delay_cycles(__ticks_dc_per_us << bit);
        }
    }

/*! \} */

};
