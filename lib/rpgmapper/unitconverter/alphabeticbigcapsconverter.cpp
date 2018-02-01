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
// incs

#include "alphabeticbigcapsconverter.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

/**
 * Lookup table.
 */
static struct {

    std::map<int, QString> m_cValues;           /**< known values */
    bool m_bInit = false;                       /**< initial init state. */

} g_cLookup;


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
// code


/**
 * Convert the given value into the user units.
 *
 * @param   nValue      value to convert
 * @return  A string holding the user value
 */
QString AlphabeticBigCapsConverter::convert(int nValue) const {

    if (!g_cLookup.m_bInit) {
        initLookup();
    }

    auto iterLookup = g_cLookup.m_cValues.find(nValue);
    if (iterLookup != g_cLookup.m_cValues.end()) {
        return (*iterLookup).second;
    }

    auto res = convertInternal(nValue);
    g_cLookup.m_cValues[nValue] = res;

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
    int n = abs(nValue);

    QList<QChar> cChars;
    while (n > nRange) {
        cChars << QChar((n / nRange) + nOffset);
        n -= nRange;
    }
    cChars << QChar((n % nRange) + nOffset);

    if (nValue < 0) {
        cChars << QChar('-');
    }

    QStringList sl;
    for (auto iter = cChars.rbegin(); iter != cChars.rend(); ++iter) {
        sl << (*iter);
    }

    return sl.join("");
}


/**
 * Initialize the lookup table.
 */
void initLookup() {

    for (int n = -100; n <= 100; ++n) {
        g_cLookup.m_cValues[n] = convertInternal(n);
    }
    g_cLookup.m_bInit = true;
}
