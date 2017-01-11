/*
 * atPOV - An ATtiny based persistence of vision
 * Copyright (C) 2017 Jens Neuhalfen
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

/*!
 * \file
 * \ingroup libPOV_tests
 *
 * \brief Test functionality of \ref libPOV::BU4094BC
 */
#include <array>

#include "BU4094BC.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::Eq;
using std::for_each;
using std::array;

class BU4094BCTest : public ::testing::Test {

protected:
    Device stubDevice;
    volatile uint8_t port;

    enum PINS {
        PIN_STROBE = 0,
        PIN_CLK = 2,
        PIN_SIN = 7,
    };

    const uint8_t ALL_PINS_MASK = 1 << PIN_STROBE | 1 << PIN_CLK | 1 << PIN_SIN;
    const uint8_t UNTOUCHED_PINS = ~ALL_PINS_MASK;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

};


TEST_F(BU4094BCTest, Creation__doesNot_TouchPort) {

    port = 0x00;
    BU4094BC sut0(stubDevice, port, PINS::PIN_STROBE, PINS::PIN_CLK, PINS::PIN_SIN);

    ASSERT_EQ(0x00, port) << "Creating BU4094BC does not touch the port (and clear bits)";


    port = 0xff;
    BU4094BC sut1(stubDevice, port, PINS::PIN_STROBE, PINS::PIN_CLK, PINS::PIN_SIN);

    ASSERT_EQ(0xff, port) << "Creating BU4094BC does not touch the port (and set bits)";
}


TEST_F(BU4094BCTest, writingABit__doesNot_TouchOtherPortBits) {

    BU4094BC sut(stubDevice, port, PINS::PIN_STROBE, PINS::PIN_CLK, PINS::PIN_SIN);

    uint8_t port_at_pre = 0xff;

    for (uint8_t mask = 0x80; mask > 0; mask <<= 1) {
        port = port_at_pre;
        sut.output(mask);

        ASSERT_EQ(port_at_pre & UNTOUCHED_PINS, port & UNTOUCHED_PINS) << "Sending data only touches configured bits";
    }
}

TEST_F(BU4094BCTest, Output__doesNot_TouchOtherPortBits) {

    BU4094BC sut(stubDevice, port, PINS::PIN_STROBE, PINS::PIN_CLK, PINS::PIN_SIN);

    std::array<uint8_t, 2> ports_at_pre = {{0x00, 0xff}};

    for_each(begin(ports_at_pre), end(ports_at_pre), [this, &sut](uint8_t port_at_pre) {
        port = port_at_pre;

        EXPECT_EQ(port_at_pre & UNTOUCHED_PINS, port & UNTOUCHED_PINS);

        sut.output(0xff);

        ASSERT_EQ(port_at_pre & UNTOUCHED_PINS, port & UNTOUCHED_PINS) << "Sending data only touches configured bits";

    });
}


