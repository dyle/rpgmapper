/*
 * romanconverter.cpp
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


// ------------------------------------------------------------
// incs

#include "romanconverter.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl


/**
 * Convert an integer to roman.
 *
 * @param   nValue      the value to convert
 * @return  the string holding the roman value
 */
static QString convertRoman(int nValue);


// ------------------------------------------------------------
// vars


/**
 * Lookup table.
 */
static std::map<int, QString> g_cLookupValues;            /**< Known cached values. */


// ------------------------------------------------------------
// code


/**
 * Convert the given value into the user units.
 *
 * @param   nValue      value to convert
 * @return  A string holding the user value
 */
QString RomanConverter::convert(int nValue) const {

    if (g_cLookupValues.empty()) {
        for (int n = 0; n <= 100; ++n) {
            g_cLookupValues[n] = convertRoman(n);
        }
    }

    auto iterLookup = g_cLookupValues.find(nValue);
    if (iterLookup != g_cLookupValues.end()) {
        return (*iterLookup).second;
    }

    auto res = convertRoman(nValue);
    g_cLookupValues[nValue] = res;

    return res;
}


/**
 * Convert an integer to roman.
 *
 * @param   nValue      the value to convert
 * @return  the string holding the roman value
 */
QString convertRoman(int nValue) {

    if (nValue < 0) {
        return QString("-") + convertRoman(-nValue);
    }
    if (nValue == 0) {
        return QString("O");
    }

    QString res = "";

    while (nValue >= 1000) {
        res += "M";
        nValue -= 1000;
    }
    while (nValue >= 900) {
        res += "CM";
        nValue -= 900;
    }
    while (nValue >= 500) {
        res += "D";
        nValue -= 500;
    }
    while (nValue >= 400) {
        res += "CD";
        nValue -= 400;
    }
    while (nValue >= 100) {
        res += "C";
        nValue -= 100;
    }
    while (nValue >= 90) {
        res += "XC";
        nValue -= 90;
    }
    while (nValue >= 50) {
        res += "L";
        nValue -= 50;
    }
    while (nValue >= 40) {
        res += "XL";
        nValue -= 40;
    }
    while (nValue >= 10) {
        res += "X";
        nValue -= 10;
    }
    while (nValue >= 9) {
        res += "IX";
        nValue -= 9;
    }
    while (nValue >= 5) {
        res += "V";
        nValue -= 5;
    }
    while (nValue >= 4) {
        res += "IV";
        nValue -= 4;
    }
    while (nValue >= 1) {
        res += "I";
        nValue -= 1;
    }
    return res;
}
