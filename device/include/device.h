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

void delay_ms(double ms);

/*! \} */
