/*
 * test_converter.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


// ------------------------------------------------------------

#include <cassert>
#include <iostream>

// rpgmapper
#include <rpgmapper/unitconverter.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    auto cNumericConverter = UnitConverter::create(UnitConverter::numeric);
    assert(cNumericConverter->convert(0) == "0");
    assert(cNumericConverter->convert(1) == "1");
    assert(cNumericConverter->convert(-1) == "-1");
    assert(cNumericConverter->convert(2) == "2");
    assert(cNumericConverter->convert(-2) == "-2");
    assert(cNumericConverter->convert(3) == "3");
    assert(cNumericConverter->convert(-3) == "-3");
    assert(cNumericConverter->convert(4) == "4");
    assert(cNumericConverter->convert(-4) == "-4");
    assert(cNumericConverter->convert(5) == "5");
    assert(cNumericConverter->convert(-5) == "-5");
    assert(cNumericConverter->convert(10) == "10");
    assert(cNumericConverter->convert(-10) == "-10");
    assert(cNumericConverter->convert(15) == "15");
    assert(cNumericConverter->convert(-15) == "-15");
    assert(cNumericConverter->convert(28) == "28");
    assert(cNumericConverter->convert(-28) == "-28");
    assert(cNumericConverter->convert(53) == "53");
    assert(cNumericConverter->convert(-53) == "-53");
    assert(cNumericConverter->convert(77) == "77");
    assert(cNumericConverter->convert(-77) == "-77");
    assert(cNumericConverter->convert(189) == "189");
    assert(cNumericConverter->convert(-189) == "-189");
    assert(cNumericConverter->convert(409) == "409");
    assert(cNumericConverter->convert(-409) == "-409");
    assert(cNumericConverter->convert(769) == "769");
    assert(cNumericConverter->convert(-769) == "-769");

    auto cAlphabeticSmallCapsConverter = UnitConverter::create(UnitConverter::alphabeticalSmallCaps);
    assert(cAlphabeticSmallCapsConverter->convert(0) == "a");
    assert(cAlphabeticSmallCapsConverter->convert(1) == "b");
    assert(cAlphabeticSmallCapsConverter->convert(-1) == "-b");
    assert(cAlphabeticSmallCapsConverter->convert(2) == "c");
    assert(cAlphabeticSmallCapsConverter->convert(-2) == "-c");
    assert(cAlphabeticSmallCapsConverter->convert(3) == "d");
    assert(cAlphabeticSmallCapsConverter->convert(-3) == "-d");
    assert(cAlphabeticSmallCapsConverter->convert(4) == "e");
    assert(cAlphabeticSmallCapsConverter->convert(-4) == "-e");
    assert(cAlphabeticSmallCapsConverter->convert(5) == "f");
    assert(cAlphabeticSmallCapsConverter->convert(-5) == "-f");
    assert(cAlphabeticSmallCapsConverter->convert(10) == "k");
    assert(cAlphabeticSmallCapsConverter->convert(-10) == "-k");
    assert(cAlphabeticSmallCapsConverter->convert(15) == "p");
    assert(cAlphabeticSmallCapsConverter->convert(-15) == "-p");
    assert(cAlphabeticSmallCapsConverter->convert(28) == "ac");
    assert(cAlphabeticSmallCapsConverter->convert(-28) == "-ac");
    assert(cAlphabeticSmallCapsConverter->convert(53) == "bb");
    assert(cAlphabeticSmallCapsConverter->convert(-53) == "-bb");
    assert(cAlphabeticSmallCapsConverter->convert(77) == "bz");
    assert(cAlphabeticSmallCapsConverter->convert(-77) == "-bz");
    assert(cAlphabeticSmallCapsConverter->convert(189) == "gh");
    assert(cAlphabeticSmallCapsConverter->convert(-189) == "-gh");
    assert(cAlphabeticSmallCapsConverter->convert(409) == "ot");
    assert(cAlphabeticSmallCapsConverter->convert(-409) == "-ot");
    assert(cAlphabeticSmallCapsConverter->convert(769) == "acp");
    assert(cAlphabeticSmallCapsConverter->convert(-769) == "-acp");

    auto cAlphabeticBigCapsConverter = UnitConverter::create(UnitConverter::alphabeticalBigCaps);
    assert(cAlphabeticBigCapsConverter->convert(0) == "A");
    assert(cAlphabeticBigCapsConverter->convert(1) == "B");
    assert(cAlphabeticBigCapsConverter->convert(-1) == "-B");
    assert(cAlphabeticBigCapsConverter->convert(2) == "C");
    assert(cAlphabeticBigCapsConverter->convert(-2) == "-C");
    assert(cAlphabeticBigCapsConverter->convert(3) == "D");
    assert(cAlphabeticBigCapsConverter->convert(-3) == "-D");
    assert(cAlphabeticBigCapsConverter->convert(4) == "E");
    assert(cAlphabeticBigCapsConverter->convert(-4) == "-E");
    assert(cAlphabeticBigCapsConverter->convert(5) == "F");
    assert(cAlphabeticBigCapsConverter->convert(-5) == "-F");
    assert(cAlphabeticBigCapsConverter->convert(10) == "K");
    assert(cAlphabeticBigCapsConverter->convert(-10) == "-K");
    assert(cAlphabeticBigCapsConverter->convert(15) == "P");
    assert(cAlphabeticBigCapsConverter->convert(-15) == "-P");
    assert(cAlphabeticBigCapsConverter->convert(28) == "AC");
    assert(cAlphabeticBigCapsConverter->convert(-28) == "-AC");
    assert(cAlphabeticBigCapsConverter->convert(53) == "BB");
    assert(cAlphabeticBigCapsConverter->convert(-53) == "-BB");
    assert(cAlphabeticBigCapsConverter->convert(77) == "BZ");
    assert(cAlphabeticBigCapsConverter->convert(-77) == "-BZ");
    assert(cAlphabeticBigCapsConverter->convert(189) == "GH");
    assert(cAlphabeticBigCapsConverter->convert(-189) == "-GH");
    assert(cAlphabeticBigCapsConverter->convert(409) == "OT");
    assert(cAlphabeticBigCapsConverter->convert(-409) == "-OT");
    assert(cAlphabeticBigCapsConverter->convert(769) == "ACP");
    assert(cAlphabeticBigCapsConverter->convert(-769) == "-ACP");

    auto cRomanConverter = UnitConverter::create(UnitConverter::roman);
    assert(cRomanConverter->convert(0) == "O");
    assert(cRomanConverter->convert(1) == "I");
    assert(cRomanConverter->convert(-1) == "-I");
    assert(cRomanConverter->convert(2) == "II");
    assert(cRomanConverter->convert(-2) == "-II");
    assert(cRomanConverter->convert(3) == "III");
    assert(cRomanConverter->convert(-3) == "-III");
    assert(cRomanConverter->convert(4) == "IV");
    assert(cRomanConverter->convert(-4) == "-IV");
    assert(cRomanConverter->convert(5) == "V");
    assert(cRomanConverter->convert(-5) == "-V");
    assert(cRomanConverter->convert(10) == "X");
    assert(cRomanConverter->convert(-10) == "-X");
    assert(cRomanConverter->convert(15) == "XV");
    assert(cRomanConverter->convert(-15) == "-XV");
    assert(cRomanConverter->convert(28) == "XXVIII");
    assert(cRomanConverter->convert(-28) == "-XXVIII");
    assert(cRomanConverter->convert(53) == "LIII");
    assert(cRomanConverter->convert(-53) == "-LIII");
    assert(cRomanConverter->convert(77) == "LXXVII");
    assert(cRomanConverter->convert(-77) == "-LXXVII");
    assert(cRomanConverter->convert(189) == "CLXXXIX");
    assert(cRomanConverter->convert(-189) == "-CLXXXIX");
    assert(cRomanConverter->convert(409) == "CDIX");
    assert(cRomanConverter->convert(-409) == "-CDIX");
    assert(cRomanConverter->convert(769) == "DCCLXIX");
    assert(cRomanConverter->convert(-769) == "-DCCLXIX");

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
