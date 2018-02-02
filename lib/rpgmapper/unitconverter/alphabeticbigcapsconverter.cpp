/*
 * alphabeticbigcapsconverter.cpp
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
// defs


/**
 * Maximum size of a string value.
 */
#define MAX_VALUE_SIZE      1024


// ------------------------------------------------------------
// incs

#include <iostream>
#include "alphabeticbigcapsconverter.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl


/**
 * Internal real conversion implementation.
 *
 * @param   nValue      the value to convert
 * @return  the string holding the value in user dimensions
 */
static QString convertInternal(int nValue);


/**
 * Initialize the lookup table.
 */
static void initLookup();


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
QString AlphabeticBigCapsConverter::convert(int nValue) const {

    if (g_cLookupValues.empty()) {
        initLookup();
    }

    auto iterLookup = g_cLookupValues.find(nValue);
    if (iterLookup != g_cLookupValues.end()) {
        return (*iterLookup).second;
    }

    auto res = convertInternal(nValue);
    g_cLookupValues[nValue] = res;

    return res;
}


/**
 * Internal real conversion implementation.
 *
 * @param   nValue      the value to convert
 * @return  the string holding the value in user dimensions
 */
QString convertInternal(int nValue) {

    if (nValue == 0) {
        return "A";
    }

    int nRange = 'Z' - 'A' + 1;
    int nOffset = 'A';
    int nAbsValue = abs(nValue);

    char sValue[MAX_VALUE_SIZE];
    int nPos = 0;

    if (nValue < 0) {
        sValue[nPos++] = '-';
    }

    while ((nAbsValue >= nRange) && (nPos < MAX_VALUE_SIZE - 1)) {
        sValue[nPos++] = (nAbsValue / nRange) - 1 + nOffset;
        nAbsValue -= nRange;
    }
    if (nPos < MAX_VALUE_SIZE - 1) {
        sValue[nPos++] = (nAbsValue % nRange) + nOffset;
    }
    if (nPos < MAX_VALUE_SIZE - 1) {
        sValue[nPos++] = 0;
    }

    return QString(sValue);
}


/**
 * Initialize the lookup table.
 */
void initLookup() {
    for (int n = 0; n <= 100; ++n) {
        g_cLookupValues[n] = convertInternal(n);
        std::cout << "n: " << n << " - " << g_cLookupValues[n].toStdString() << std::endl;
    }
}
