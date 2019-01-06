/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/numerals.hpp>

using namespace rpgmapper::model;


TEST(NumeralsTest, TestInvalidNumeralConverter) {

    auto converter = NumeralConverter::create("foo");

    ASSERT_FALSE(converter->isValid());
}


TEST(NumeralsTest, TestNumericConverter) {

    auto converter = NumeralConverter::create("numeric");

    ASSERT_TRUE(converter->isValid());
    EXPECT_EQ(converter->convert(0).toStdString(), "0");
    EXPECT_EQ(converter->convert(1).toStdString(), "1");
    EXPECT_EQ(converter->convert(-1).toStdString(), "-1");
    EXPECT_EQ(converter->convert(2).toStdString(), "2");
    EXPECT_EQ(converter->convert(-2).toStdString(), "-2");
    EXPECT_EQ(converter->convert(3).toStdString(), "3");
    EXPECT_EQ(converter->convert(-3).toStdString(), "-3");
    EXPECT_EQ(converter->convert(4).toStdString(), "4");
    EXPECT_EQ(converter->convert(-4).toStdString(), "-4");
    EXPECT_EQ(converter->convert(5).toStdString(), "5");
    EXPECT_EQ(converter->convert(-5).toStdString(), "-5");
    EXPECT_EQ(converter->convert(10).toStdString(), "10");
    EXPECT_EQ(converter->convert(-10).toStdString(), "-10");
    EXPECT_EQ(converter->convert(15).toStdString(), "15");
    EXPECT_EQ(converter->convert(-15).toStdString(), "-15");
    EXPECT_EQ(converter->convert(28).toStdString(), "28");
    EXPECT_EQ(converter->convert(-28).toStdString(), "-28");
    EXPECT_EQ(converter->convert(53).toStdString(), "53");
    EXPECT_EQ(converter->convert(-53).toStdString(), "-53");
    EXPECT_EQ(converter->convert(77).toStdString(), "77");
    EXPECT_EQ(converter->convert(-77).toStdString(), "-77");
    EXPECT_EQ(converter->convert(189).toStdString(), "189");
    EXPECT_EQ(converter->convert(-189).toStdString(), "-189");
    EXPECT_EQ(converter->convert(409).toStdString(), "409");
    EXPECT_EQ(converter->convert(-409).toStdString(), "-409");
    EXPECT_EQ(converter->convert(769).toStdString(), "769");
    EXPECT_EQ(converter->convert(-769).toStdString(), "-769");
}


TEST(NumeralsTest, TestAlphaSmallConverter) {

    auto converter = NumeralConverter::create("alphaSmall");

    ASSERT_TRUE(converter->isValid());
    EXPECT_EQ(converter->convert(0).toStdString(), "a");
    EXPECT_EQ(converter->convert(1).toStdString(), "b");
    EXPECT_EQ(converter->convert(-1).toStdString(), "-b");
    EXPECT_EQ(converter->convert(2).toStdString(), "c");
    EXPECT_EQ(converter->convert(-2).toStdString(), "-c");
    EXPECT_EQ(converter->convert(3).toStdString(), "d");
    EXPECT_EQ(converter->convert(-3).toStdString(), "-d");
    EXPECT_EQ(converter->convert(4).toStdString(), "e");
    EXPECT_EQ(converter->convert(-4).toStdString(), "-e");
    EXPECT_EQ(converter->convert(5).toStdString(), "f");
    EXPECT_EQ(converter->convert(-5).toStdString(), "-f");
    EXPECT_EQ(converter->convert(10).toStdString(), "k");
    EXPECT_EQ(converter->convert(-10).toStdString(), "-k");
    EXPECT_EQ(converter->convert(15).toStdString(), "p");
    EXPECT_EQ(converter->convert(-15).toStdString(), "-p");
    EXPECT_EQ(converter->convert(28).toStdString(), "ac");
    EXPECT_EQ(converter->convert(-28).toStdString(), "-ac");
    EXPECT_EQ(converter->convert(53).toStdString(), "bb");
    EXPECT_EQ(converter->convert(-53).toStdString(), "-bb");
    EXPECT_EQ(converter->convert(77).toStdString(), "bz");
    EXPECT_EQ(converter->convert(-77).toStdString(), "-bz");
    EXPECT_EQ(converter->convert(189).toStdString(), "gh");
    EXPECT_EQ(converter->convert(-189).toStdString(), "-gh");
    EXPECT_EQ(converter->convert(409).toStdString(), "ot");
    EXPECT_EQ(converter->convert(-409).toStdString(), "-ot");
    EXPECT_EQ(converter->convert(769).toStdString(), "acp");
    EXPECT_EQ(converter->convert(-769).toStdString(), "-acp");
}


TEST(NumeralsTest, TestAlphaBigConverter) {

    auto converter = NumeralConverter::create("alphaBig");

    ASSERT_TRUE(converter->isValid());
    EXPECT_EQ(converter->convert(0).toStdString(), "A");
    EXPECT_EQ(converter->convert(1).toStdString(), "B");
    EXPECT_EQ(converter->convert(-1).toStdString(), "-B");
    EXPECT_EQ(converter->convert(2).toStdString(), "C");
    EXPECT_EQ(converter->convert(-2).toStdString(), "-C");
    EXPECT_EQ(converter->convert(3).toStdString(), "D");
    EXPECT_EQ(converter->convert(-3).toStdString(), "-D");
    EXPECT_EQ(converter->convert(4).toStdString(), "E");
    EXPECT_EQ(converter->convert(-4).toStdString(), "-E");
    EXPECT_EQ(converter->convert(5).toStdString(), "F");
    EXPECT_EQ(converter->convert(-5).toStdString(), "-F");
    EXPECT_EQ(converter->convert(10).toStdString(), "K");
    EXPECT_EQ(converter->convert(-10).toStdString(), "-K");
    EXPECT_EQ(converter->convert(15).toStdString(), "P");
    EXPECT_EQ(converter->convert(-15).toStdString(), "-P");
    EXPECT_EQ(converter->convert(28).toStdString(), "AC");
    EXPECT_EQ(converter->convert(-28).toStdString(), "-AC");
    EXPECT_EQ(converter->convert(53).toStdString(), "BB");
    EXPECT_EQ(converter->convert(-53).toStdString(), "-BB");
    EXPECT_EQ(converter->convert(77).toStdString(), "BZ");
    EXPECT_EQ(converter->convert(-77).toStdString(), "-BZ");
    EXPECT_EQ(converter->convert(189).toStdString(), "GH");
    EXPECT_EQ(converter->convert(-189).toStdString(), "-GH");
    EXPECT_EQ(converter->convert(409).toStdString(), "OT");
    EXPECT_EQ(converter->convert(-409).toStdString(), "-OT");
    EXPECT_EQ(converter->convert(769).toStdString(), "ACP");
    EXPECT_EQ(converter->convert(-769).toStdString(), "-ACP");
}


TEST(NumeralsTest, TestRomanConverter) {

    auto converter = NumeralConverter::create("roman");

    ASSERT_TRUE(converter->isValid());
    EXPECT_EQ(converter->convert(0).toStdString(), "O");
    EXPECT_EQ(converter->convert(1).toStdString(), "I");
    EXPECT_EQ(converter->convert(-1).toStdString(), "-I");
    EXPECT_EQ(converter->convert(2).toStdString(), "II");
    EXPECT_EQ(converter->convert(-2).toStdString(), "-II");
    EXPECT_EQ(converter->convert(3).toStdString(), "III");
    EXPECT_EQ(converter->convert(-3).toStdString(), "-III");
    EXPECT_EQ(converter->convert(4).toStdString(), "IV");
    EXPECT_EQ(converter->convert(-4).toStdString(), "-IV");
    EXPECT_EQ(converter->convert(5).toStdString(), "V");
    EXPECT_EQ(converter->convert(-5).toStdString(), "-V");
    EXPECT_EQ(converter->convert(10).toStdString(), "X");
    EXPECT_EQ(converter->convert(-10).toStdString(), "-X");
    EXPECT_EQ(converter->convert(15).toStdString(), "XV");
    EXPECT_EQ(converter->convert(-15).toStdString(), "-XV");
    EXPECT_EQ(converter->convert(28).toStdString(), "XXVIII");
    EXPECT_EQ(converter->convert(-28).toStdString(), "-XXVIII");
    EXPECT_EQ(converter->convert(53).toStdString(), "LIII");
    EXPECT_EQ(converter->convert(-53).toStdString(), "-LIII");
    EXPECT_EQ(converter->convert(77).toStdString(), "LXXVII");
    EXPECT_EQ(converter->convert(-77).toStdString(), "-LXXVII");
    EXPECT_EQ(converter->convert(189).toStdString(), "CLXXXIX");
    EXPECT_EQ(converter->convert(-189).toStdString(), "-CLXXXIX");
    EXPECT_EQ(converter->convert(409).toStdString(), "CDIX");
    EXPECT_EQ(converter->convert(-409).toStdString(), "-CDIX");
    EXPECT_EQ(converter->convert(769).toStdString(), "DCCLXIX");
    EXPECT_EQ(converter->convert(-769).toStdString(), "-DCCLXIX");
}
