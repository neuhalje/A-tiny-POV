/*
 * atPOV - An ATtiny based persistence of vision
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
 * \brief Test functionality of \ref libPOV::Font
 */

#include "font.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::Eq;

class FontTest : public ::testing::Test {
protected:

    Font *_sut;

    virtual void SetUp() {
        _sut = new Font();
    }

    virtual void TearDown() {
        delete _sut;
    }

    Font &  sut() {
        return *_sut;
    }
};


TEST_F(FontTest, ExistingGlyphIsFound) {
    uint8_t buffer[sut().glyph_width()];
    EXPECT_TRUE(sut().read_font_char_columns('a', buffer));
}


TEST_F(FontTest,  PassingNullAsBufferFails) {
    EXPECT_FALSE(sut().read_font_char_columns('a', nullptr));
}

TEST_F(FontTest,  NotExistingGlyphIsNotFound) {
    uint8_t buffer[sut().glyph_width()];
    EXPECT_FALSE(sut().read_font_char_columns(0xff, buffer)) << "The glyph for 0xff should not be defined";
}

TEST_F(FontTest,  GlyphSlashIsReturnedCorrectly) {
    uint8_t retrieved_glyph[sut().glyph_width()];
    bzero(retrieved_glyph, sizeof(retrieved_glyph));

    EXPECT_THAT(sut().read_font_char_columns('/', retrieved_glyph), Eq(true)) << "/ should be found";

    const uint8_t expected_glyph[]{1, 2, 4, 8, 16};

    for (int i = 0; i < sut().glyph_width(); ++i) {
        EXPECT_EQ(expected_glyph[i], retrieved_glyph[i]) << "expected and retrieved differ at index " << i;
    }
}

TEST_F(FontTest, UnknownGlyphIsReturnedAsOpaque) {
    uint8_t retrieved_glyph[sut().glyph_width()];
    bzero(retrieved_glyph, sizeof(retrieved_glyph));

    EXPECT_THAT(sut().read_font_char_columns(0xff, retrieved_glyph), Eq(false)) << "0xff should NOT be found";

    const uint8_t expected_glyph[]{0xff, 0xff, 0xff, 0xff, 0xff};

    for (int i = 0; i < sut().glyph_width(); ++i) {
        EXPECT_EQ(expected_glyph[i], retrieved_glyph[i]) << "expected and retrieved differ at index " << i;
    }
}

TEST_F(FontTest,  UppercaseGlyphsAreFound) {
    uint8_t buffer[sut().glyph_width()];
    EXPECT_TRUE(sut().read_font_char_columns('A', buffer))
                        << "For not existing upper-case  glyphs: return matching lower-case glyph";
}
