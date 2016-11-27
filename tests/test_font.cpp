/*
 * atPOV - An ATtiny based persistence of view
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

/*!
 * \file
 * \ingroup libPOV_tests
 *
 * \brief Test functionality of the font
 */

extern "C" {
#include "font.h"
}

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::Eq;


TEST(Font, ExistingGlyphIsFound) {
    uint8_t buffer[8];
    EXPECT_TRUE(read_font_char_columns('a', buffer));
}


TEST(Font, PassingNullAsBufferFails) {
    EXPECT_FALSE(read_font_char_columns('a', nullptr));
}

TEST(Font, NotExistingGlyphIsNotFound) {
    uint8_t buffer[8];
    EXPECT_FALSE(read_font_char_columns(0xff, buffer)) << "The glyph for 0xff should not be defined";
}

TEST(Font, GlyphSlashIsReturnedCorrectly) {
    uint8_t retrieved_glyph[8];
    bzero(retrieved_glyph, sizeof(retrieved_glyph));

    EXPECT_THAT(read_font_char_columns('/', retrieved_glyph), Eq(true)) << "/ should be found";

    const uint8_t expected_glyph[]{1, 2, 4, 8, 16};

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(expected_glyph[i], retrieved_glyph[i]) << "expected and retrieved differ at index " << i;
    }
}

TEST(Font, UnknownGlyphSlashIsReturnedAsOpaque) {
    uint8_t retrieved_glyph[8];
    bzero(retrieved_glyph, sizeof(retrieved_glyph));

    EXPECT_THAT(read_font_char_columns(0xff, retrieved_glyph), Eq(false)) << "0xff should NOT be found";

    const uint8_t expected_glyph[]{0xff, 0xff, 0xff, 0xff, 0xff};

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(expected_glyph[i], retrieved_glyph[i]) << "expected and retrieved differ at index " << i;
    }
}