/*
 * alphabetic.hpp
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
// def

/**
 * Maximum size of a string value.
 */
#define MAX_VALUE_SIZE      1000


// ------------------------------------------------------------
// incs

#include "alphabetic.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Convert a value to alphanumeric
 *
 * @param   nValue      the value
 * @param   bBig        big or small caps
 * @return  a string holding the value converted to alphabetic
 */
QString rpgmapper::model::convertAlpha(int nValue, bool bBig) {

    int nOffset = bBig ? 'A' : 'a';
    if (nValue == 0) {
        return QString(QChar(nOffset));
    }

    static int const nRange = 26;
    int nAbsValue = abs(nValue);

    char sValue[MAX_VALUE_SIZE + 1];
    int nPos = 0;

    if (nValue < 0) {
        sValue[nPos++] = '-';
    }
    while ((nAbsValue >= nRange) && (nPos < MAX_VALUE_SIZE)) {
        int nMultiplier = nAbsValue / nRange;
        sValue[nPos++] = static_cast<char>(nMultiplier - 1 + nOffset);
        nAbsValue -= nMultiplier * nRange;
    }
    if (nPos < MAX_VALUE_SIZE) {
        sValue[nPos++] = static_cast<char>((nAbsValue % nRange) + nOffset);
    }
    if (nPos < MAX_VALUE_SIZE) {
        sValue[nPos] = 0;
    }

    return QString(sValue);
}
